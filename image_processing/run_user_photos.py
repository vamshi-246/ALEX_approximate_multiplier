"""
Process user-provided images through ALEX approximate multiplier comparison.
Runs at 512x512 resolution for higher detail.
"""

import os
import sys
import time
import numpy as np
from PIL import Image
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.gridspec import GridSpec

from alex_multiplier_model import build_approx_lut, build_exact_lut

# --- Setup ---
RESULTS_DIR = os.path.join(os.path.dirname(__file__), "results_user_photos")
os.makedirs(RESULTS_DIR, exist_ok=True)

IMG_SIZE = 512  # Higher resolution

print("Building lookup tables...")
t0 = time.time()
APPROX_LUT = build_approx_lut()
EXACT_LUT  = build_exact_lut()
BIAS_LUT = APPROX_LUT.astype(np.int32) - EXACT_LUT.astype(np.int32)
MEAN_BIAS = float(np.mean(BIAS_LUT))
print(f"  Done in {time.time()-t0:.1f}s  (mean bias={MEAN_BIAS:.0f})")

def mult_exact(a, b):
    return EXACT_LUT[a.astype(np.uint8), b.astype(np.uint8)].astype(np.int32)

def mult_approx_raw(a, b):
    return APPROX_LUT[a.astype(np.uint8), b.astype(np.uint8)].astype(np.int32)

def mult_approx_comp(a, b):
    a8, b8 = a.astype(np.uint8), b.astype(np.uint8)
    return APPROX_LUT[a8, b8].astype(np.int32) - int(round(MEAN_BIAS))

def compute_psnr(ref, test):
    mse = np.mean((ref.astype(np.float64) - test.astype(np.float64)) ** 2)
    if mse == 0: return float('inf')
    return 10.0 * np.log10(255.0**2 / mse)

def compute_ssim(ref, test):
    ref, test = ref.astype(np.float64), test.astype(np.float64)
    C1, C2 = (0.01*255)**2, (0.03*255)**2
    mu_x, mu_y = np.mean(ref), np.mean(test)
    sig_x2, sig_y2 = np.var(ref), np.var(test)
    sig_xy = np.mean((ref - mu_x) * (test - mu_y))
    return float(((2*mu_x*mu_y+C1)*(2*sig_xy+C2)) / ((mu_x**2+mu_y**2+C1)*(sig_x2+sig_y2+C2)))

def convolve(image, coeffs, signs, divisor, mult_fn):
    h, w = image.shape
    kh, kw = len(coeffs), len(coeffs[0])
    pad_h, pad_w = kh//2, kw//2
    padded = np.pad(image, ((pad_h,pad_h),(pad_w,pad_w)), mode='edge')
    output = np.zeros((h,w), dtype=np.float64)
    for ki in range(kh):
        for kj in range(kw):
            coeff, sign = int(coeffs[ki][kj]), signs[ki][kj]
            if coeff == 0: continue
            window = padded[ki:ki+h, kj:kj+w].astype(np.uint8)
            coeff_arr = np.full_like(window, coeff, dtype=np.uint8)
            output += sign * mult_fn(window, coeff_arr).astype(np.float64)
    return output / divisor if divisor else output

# --- Kernels ---
KERNELS = {
    "Gaussian Blur 3x3": {
        "coeffs": [[1,2,1],[2,4,2],[1,2,1]], "signs": [[1]*3]*3, "divisor": 16,
        "desc": "Low-pass smoothing"
    },
    "Gaussian Blur 5x5": {
        "coeffs": [[1,4,7,4,1],[4,16,26,16,4],[7,26,41,26,7],[4,16,26,16,4],[1,4,7,4,1]],
        "signs": [[1]*5]*5, "divisor": 273, "desc": "Stronger smoothing"
    },
    "Sharpening": {
        "coeffs": [[0,1,0],[1,9,1],[1,0,1]],
        "signs": [[1,-1,1],[-1,1,-1],[1,-1,1]], "divisor": 1,
        "desc": "Edge enhancement"
    },
    "Sobel Horizontal": {
        "coeffs": [[1,2,1],[0,0,0],[1,2,1]],
        "signs": [[-1,-1,-1],[1,1,1],[1,1,1]], "divisor": 1,
        "desc": "Horizontal edges"
    },
    "Sobel Vertical": {
        "coeffs": [[1,0,1],[2,0,2],[1,0,1]],
        "signs": [[-1,1,1],[-1,1,1],[-1,1,1]], "divisor": 1,
        "desc": "Vertical edges"
    },
    "Laplacian": {
        "coeffs": [[0,1,0],[1,4,1],[0,1,0]],
        "signs": [[1,1,1],[1,-1,1],[1,1,1]], "divisor": 1,
        "desc": "Edge detection"
    },
    "Brightness x0.7": {
        "coeffs": [[179]], "signs": [[1]], "divisor": 256,
        "desc": "Darken (179/256)"
    },
    "Brightness x1.3": {
        "coeffs": [[166]], "signs": [[1]], "divisor": 128,
        "desc": "Brighten (166/128)"
    },
}

def create_comparison(original, exact, approx_raw, approx_comp, 
                      kernel_name, desc, m_raw, m_comp, save_path):
    """5-panel comparison figure."""
    err_raw = np.clip(np.abs(exact.astype(float)-approx_raw.astype(float))*5, 0, 255).astype(np.uint8)
    err_comp = np.clip(np.abs(exact.astype(float)-approx_comp.astype(float))*5, 0, 255).astype(np.uint8)
    
    fig = plt.figure(figsize=(22, 6), dpi=150)
    fig.patch.set_facecolor('#1a1a2e')
    gs = GridSpec(1, 6, width_ratios=[1,1,1,1,1,0.05], wspace=0.06)
    
    panels = [
        ("Original", original, 'gray'),
        ("Exact Multiplier", exact, 'gray'),
        ("ALEX Approx (Raw)", approx_raw, 'gray'),
        ("ALEX Bias-Compensated", approx_comp, 'gray'),
    ]
    
    for i, (title, data, cmap) in enumerate(panels):
        ax = fig.add_subplot(gs[0, i])
        ax.imshow(data, cmap=cmap, vmin=0, vmax=255)
        ax.set_title(title, color='white', fontsize=10, fontweight='bold', pad=6)
        ax.axis('off')
    
    # Error panel (stacked: raw top, compensated bottom)
    ax = fig.add_subplot(gs[0, 4])
    sep = np.ones((4, err_raw.shape[1]), dtype=np.uint8) * 128
    combined = np.vstack([err_raw, sep, err_comp])
    im = ax.imshow(combined, cmap='hot', vmin=0, vmax=255)
    ax.axhline(y=err_raw.shape[0]+2, color='cyan', linewidth=1)
    ax.text(5, err_raw.shape[0]//2, 'Raw err', color='cyan', fontsize=7, fontweight='bold')
    ax.text(5, err_raw.shape[0]+4+err_comp.shape[0]//2, 'Comp err', color='cyan', fontsize=7, fontweight='bold')
    ax.set_title("Error Map (x5)", color='white', fontsize=10, fontweight='bold', pad=6)
    ax.axis('off')
    
    cax = fig.add_subplot(gs[0, 5])
    cbar = plt.colorbar(im, cax=cax)
    cbar.ax.yaxis.set_tick_params(color='white')
    cbar.outline.set_edgecolor('white')
    plt.setp(cbar.ax.yaxis.get_ticklabels(), color='white', fontsize=7)
    
    raw_s  = f"Raw: PSNR={m_raw['psnr']:.1f}dB SSIM={m_raw['ssim']:.4f} MSE={m_raw['mse']:.1f}"
    comp_s = f"Comp: PSNR={m_comp['psnr']:.1f}dB SSIM={m_comp['ssim']:.4f} MSE={m_comp['mse']:.1f}"
    fig.suptitle(f"{kernel_name} -- {desc}\n{raw_s}  |  {comp_s}",
                 color='#00d4ff', fontsize=12, fontweight='bold', y=1.02)
    
    plt.savefig(save_path, bbox_inches='tight', facecolor=fig.get_facecolor(),
                edgecolor='none', pad_inches=0.3)
    plt.close(fig)


def process_image(img_path, img_label):
    """Process a single image through all kernels."""
    print(f"\n{'='*60}")
    print(f"  Processing: {img_label}")
    print(f"  Source: {os.path.basename(img_path)}")
    print(f"  Target resolution: {IMG_SIZE}x{IMG_SIZE}")
    print(f"{'='*60}")
    
    # Load, resize, convert to grayscale
    img = Image.open(img_path).convert('L').resize((IMG_SIZE, IMG_SIZE), Image.LANCZOS)
    img_arr = np.array(img)
    
    # Save grayscale input
    Image.fromarray(img_arr).save(os.path.join(RESULTS_DIR, f"{img_label}_input_gray.png"))
    print(f"  Shape: {img_arr.shape}, range: [{img_arr.min()}, {img_arr.max()}]")
    
    all_metrics = []
    
    for kernel_name, kinfo in KERNELS.items():
        coeffs, signs, divisor = kinfo["coeffs"], kinfo["signs"], kinfo["divisor"]
        desc = kinfo["desc"]
        print(f"\n  [{kernel_name}] {desc}...")
        
        t0 = time.time()
        exact = np.clip(convolve(img_arr, coeffs, signs, divisor, mult_exact), 0, 255).astype(np.uint8)
        raw   = np.clip(convolve(img_arr, coeffs, signs, divisor, mult_approx_raw), 0, 255).astype(np.uint8)
        comp  = np.clip(convolve(img_arr, coeffs, signs, divisor, mult_approx_comp), 0, 255).astype(np.uint8)
        elapsed = time.time() - t0
        
        m_raw  = {"psnr": compute_psnr(exact, raw),  "ssim": compute_ssim(exact, raw),
                   "mse": float(np.mean((exact.astype(float)-raw.astype(float))**2)),
                   "max_err": float(np.max(np.abs(exact.astype(float)-raw.astype(float))))}
        m_comp = {"psnr": compute_psnr(exact, comp), "ssim": compute_ssim(exact, comp),
                   "mse": float(np.mean((exact.astype(float)-comp.astype(float))**2)),
                   "max_err": float(np.max(np.abs(exact.astype(float)-comp.astype(float))))}
        
        print(f"    RAW:  PSNR={m_raw['psnr']:.1f}dB  SSIM={m_raw['ssim']:.4f}  MSE={m_raw['mse']:.1f}")
        print(f"    COMP: PSNR={m_comp['psnr']:.1f}dB  SSIM={m_comp['ssim']:.4f}  MSE={m_comp['mse']:.1f}")
        print(f"    Time: {elapsed:.1f}s")
        
        safe = kernel_name.replace(" ","_").replace(".","")
        fname = f"{img_label}_{safe}.png"
        create_comparison(img_arr, exact, raw, comp, kernel_name, desc, m_raw, m_comp,
                          os.path.join(RESULTS_DIR, fname))
        print(f"    -> {fname}")
        
        all_metrics.append({"kernel": kernel_name, "m_raw": m_raw, "m_comp": m_comp})
    
    return all_metrics


def create_combined_summary(metrics_by_image, save_path):
    """Combined PSNR chart for all images."""
    n_images = len(metrics_by_image)
    fig, axes = plt.subplots(1, n_images, figsize=(10*n_images, 7), dpi=150)
    if n_images == 1: axes = [axes]
    fig.patch.set_facecolor('#1a1a2e')
    
    for idx, (label, metrics) in enumerate(metrics_by_image.items()):
        ax = axes[idx]
        ax.set_facecolor('#16213e')
        
        names = [m["kernel"] for m in metrics]
        psnr_raw  = [min(m["m_raw"]["psnr"], 60) for m in metrics]
        psnr_comp = [min(m["m_comp"]["psnr"], 60) for m in metrics]
        ssim_comp = [m["m_comp"]["ssim"] for m in metrics]
        
        x = np.arange(len(names))
        w = 0.35
        ax.barh(x-w/2, psnr_raw, w, label='Raw Approx', color='#ff6b6b', alpha=0.85)
        ax.barh(x+w/2, psnr_comp, w, label='Bias-Compensated', color='#00d4ff', alpha=0.85)
        
        for i, (pr, pc, sc) in enumerate(zip(psnr_raw, psnr_comp, ssim_comp)):
            ax.text(pr+0.3, i-w/2, f"{pr:.1f}", va='center', color='#ff9999', fontsize=7)
            ax.text(pc+0.3, i+w/2, f"{pc:.1f} (SSIM={sc:.3f})", va='center', color='#66e5ff', fontsize=7)
        
        ax.set_yticks(x)
        ax.set_yticklabels(names, color='white', fontsize=9)
        ax.set_xlabel('PSNR (dB) -- higher is better', color='white', fontsize=10)
        ax.set_title(f'{label}', color='#00d4ff', fontsize=13, fontweight='bold')
        ax.legend(fontsize=9, loc='lower right', facecolor='#16213e', edgecolor='#444', labelcolor='white')
        ax.tick_params(colors='white')
        for s in ['bottom','left']: ax.spines[s].set_color('white')
        for s in ['top','right']: ax.spines[s].set_visible(False)
        ax.set_xlim(0, max(max(psnr_raw), max(psnr_comp)) * 1.35)
    
    plt.tight_layout()
    plt.savefig(save_path, bbox_inches='tight', facecolor=fig.get_facecolor(),
                edgecolor='none', pad_inches=0.3)
    plt.close(fig)


# --- Main ---
if __name__ == "__main__":
    base_dir = os.path.dirname(os.path.dirname(__file__))
    
    images = [
        (os.path.join(base_dir, "WhatsApp Image 2026-04-22 at 1.38.19 AM.jpeg"), "Photo1"),
        (os.path.join(base_dir, "WhatsApp Image 2026-04-22 at 1.38.32 AM.jpeg"), "Photo2"),
    ]
    
    all_results = {}
    for img_path, label in images:
        if os.path.exists(img_path):
            all_results[label] = process_image(img_path, label)
        else:
            print(f"WARNING: Not found: {img_path}")
    
    # Combined summary
    print(f"\n{'-'*60}")
    print("  Generating combined summary...")
    create_combined_summary(all_results, os.path.join(RESULTS_DIR, "summary_psnr_both_photos.png"))
    print("    -> summary_psnr_both_photos.png")
    
    print(f"\n{'='*60}")
    print(f"  All results: {os.path.abspath(RESULTS_DIR)}")
    print(f"{'='*60}")
