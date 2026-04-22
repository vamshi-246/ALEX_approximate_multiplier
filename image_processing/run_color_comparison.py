"""
COLOR Image Processing Comparison: ALEX Approximate Multiplier
Processes each RGB channel independently, generates:
  1. Full-color side-by-side comparisons
  2. Animated GIFs (Exact -> Raw -> Compensated transition)
  3. Diagonal split-view overlays
  4. Error heatmap overlaid on the color image
  5. Zoomed-in detail crops with magnification
  6. Per-channel error analysis
  7. Publication-quality montage
"""

import os, sys, time, math
import numpy as np
from PIL import Image, ImageDraw, ImageFont, ImageFilter
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.gridspec import GridSpec
import matplotlib.patches as patches

from alex_multiplier_model import build_approx_lut, build_exact_lut

# --- Setup ---
RESULTS_DIR = os.path.join(os.path.dirname(__file__), "results_color")
os.makedirs(RESULTS_DIR, exist_ok=True)
IMG_SIZE = 512

print("Building lookup tables...")
t0 = time.time()
APPROX_LUT = build_approx_lut()
EXACT_LUT  = build_exact_lut()
BIAS_LUT   = APPROX_LUT.astype(np.int32) - EXACT_LUT.astype(np.int32)
MEAN_BIAS  = float(np.mean(BIAS_LUT))
print(f"  Done in {time.time()-t0:.1f}s  (mean bias={MEAN_BIAS:.0f})")

# --- Multiplier functions ---
def mult_exact(a, b):
    return EXACT_LUT[a.astype(np.uint8), b.astype(np.uint8)].astype(np.int32)

def mult_approx_raw(a, b):
    return APPROX_LUT[a.astype(np.uint8), b.astype(np.uint8)].astype(np.int32)

def mult_approx_comp(a, b):
    a8, b8 = a.astype(np.uint8), b.astype(np.uint8)
    return APPROX_LUT[a8, b8].astype(np.int32) - int(round(MEAN_BIAS))

# --- Metrics ---
def compute_psnr(ref, test):
    mse = np.mean((ref.astype(np.float64) - test.astype(np.float64)) ** 2)
    if mse < 1e-10: return float('inf')
    return 10.0 * np.log10(255.0**2 / mse)

def compute_ssim(ref, test):
    ref, test = ref.astype(np.float64), test.astype(np.float64)
    C1, C2 = (0.01*255)**2, (0.03*255)**2
    mu_x, mu_y = np.mean(ref), np.mean(test)
    sig_x2, sig_y2 = np.var(ref), np.var(test)
    sig_xy = np.mean((ref - mu_x) * (test - mu_y))
    return float(((2*mu_x*mu_y+C1)*(2*sig_xy+C2)) / ((mu_x**2+mu_y**2+C1)*(sig_x2+sig_y2+C2)))

# --- Convolution ---
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

def convolve_color(img_rgb, coeffs, signs, divisor, mult_fn):
    """Apply convolution to each RGB channel independently."""
    result = np.zeros_like(img_rgb, dtype=np.float64)
    for c in range(3):
        result[:,:,c] = convolve(img_rgb[:,:,c], coeffs, signs, divisor, mult_fn)
    return np.clip(result, 0, 255).astype(np.uint8)

# --- Kernels ---
KERNELS = {
    "Gaussian Blur 3x3": {
        "coeffs": [[1,2,1],[2,4,2],[1,2,1]], "signs": [[1]*3]*3, "divisor": 16,
        "desc": "Low-pass smoothing", "type": "filter"
    },
    "Gaussian Blur 5x5": {
        "coeffs": [[1,4,7,4,1],[4,16,26,16,4],[7,26,41,26,7],[4,16,26,16,4],[1,4,7,4,1]],
        "signs": [[1]*5]*5, "divisor": 273, "desc": "Stronger smoothing", "type": "filter"
    },
    "Sharpening": {
        "coeffs": [[0,1,0],[1,9,1],[1,0,1]],
        "signs": [[1,-1,1],[-1,1,-1],[1,-1,1]], "divisor": 1,
        "desc": "Edge enhancement", "type": "filter"
    },
    "Sobel Horizontal": {
        "coeffs": [[1,2,1],[0,0,0],[1,2,1]],
        "signs": [[-1,-1,-1],[1,1,1],[1,1,1]], "divisor": 1,
        "desc": "Horizontal edges", "type": "edge"
    },
    "Brightness x0.7": {
        "coeffs": [[179]], "signs": [[1]], "divisor": 256,
        "desc": "Darken", "type": "pixel"
    },
    "Brightness x1.3": {
        "coeffs": [[166]], "signs": [[1]], "divisor": 128,
        "desc": "Brighten", "type": "pixel"
    },
}


# ========================
#  COOL VISUALIZATIONS
# ========================

def create_diagonal_split(exact_rgb, approx_rgb, title, save_path):
    """Diagonal split-view: exact on upper-left, approx on lower-right."""
    h, w, _ = exact_rgb.shape
    composite = exact_rgb.copy()
    
    # Create diagonal mask
    Y, X = np.mgrid[0:h, 0:w]
    mask = X > Y * w / h  # lower-right triangle
    for c in range(3):
        composite[:,:,c] = np.where(mask, approx_rgb[:,:,c], exact_rgb[:,:,c])
    
    fig, ax = plt.subplots(figsize=(8, 8), dpi=150)
    fig.patch.set_facecolor('#1a1a2e')
    ax.imshow(composite)
    
    # Draw diagonal line
    ax.plot([0, w], [0, h], color='#00d4ff', linewidth=2, alpha=0.8)
    
    # Labels
    ax.text(w*0.15, h*0.85, 'EXACT', color='#00ff88', fontsize=14,
            fontweight='bold', ha='center', va='center',
            bbox=dict(boxstyle='round,pad=0.3', facecolor='black', alpha=0.7))
    ax.text(w*0.85, h*0.15, 'ALEX\nAPPROX', color='#ff6b6b', fontsize=14,
            fontweight='bold', ha='center', va='center',
            bbox=dict(boxstyle='round,pad=0.3', facecolor='black', alpha=0.7))

    ax.set_title(title, color='#00d4ff', fontsize=14, fontweight='bold', pad=10)
    ax.axis('off')
    plt.savefig(save_path, bbox_inches='tight', facecolor=fig.get_facecolor(),
                edgecolor='none', pad_inches=0.2)
    plt.close(fig)


def create_error_overlay(original_rgb, exact_rgb, approx_rgb, title, save_path):
    """Overlay color-coded error heatmap on the original image."""
    error = np.sqrt(np.mean((exact_rgb.astype(float) - approx_rgb.astype(float))**2, axis=2))
    error_norm = np.clip(error / max(error.max(), 1) * 255, 0, 255).astype(np.uint8)
    
    fig, axes = plt.subplots(1, 3, figsize=(20, 7), dpi=150)
    fig.patch.set_facecolor('#1a1a2e')
    
    # Panel 1: Original with error overlay
    ax = axes[0]
    ax.imshow(original_rgb)
    im = ax.imshow(error_norm, cmap='jet', alpha=0.45, vmin=0, vmax=max(error_norm.max(), 1))
    ax.set_title('Error Overlay on Original', color='white', fontsize=12, fontweight='bold')
    ax.axis('off')
    
    # Panel 2: Pure error heatmap
    ax = axes[1]
    im2 = ax.imshow(error, cmap='inferno', vmin=0)
    ax.set_title('Per-Pixel RGB Error Magnitude', color='white', fontsize=12, fontweight='bold')
    ax.axis('off')
    cbar = plt.colorbar(im2, ax=ax, fraction=0.046, pad=0.04)
    cbar.ax.yaxis.set_tick_params(color='white')
    cbar.outline.set_edgecolor('#444')
    plt.setp(cbar.ax.yaxis.get_ticklabels(), color='white', fontsize=8)
    
    # Panel 3: Per-channel error bars
    ax = axes[2]
    ax.set_facecolor('#16213e')
    channels = ['Red', 'Green', 'Blue']
    colors_ch = ['#ff4444', '#44ff44', '#4488ff']
    err_per_ch = []
    for c in range(3):
        ch_err = np.abs(exact_rgb[:,:,c].astype(float) - approx_rgb[:,:,c].astype(float))
        err_per_ch.append(ch_err.flatten())
    
    bp = ax.boxplot(err_per_ch, labels=channels, patch_artist=True, widths=0.5,
                    medianprops=dict(color='white', linewidth=2),
                    whiskerprops=dict(color='white'),
                    capprops=dict(color='white'),
                    flierprops=dict(marker='.', markerfacecolor='gray', markersize=1, alpha=0.3))
    for patch, color in zip(bp['boxes'], colors_ch):
        patch.set_facecolor(color)
        patch.set_alpha(0.7)
    ax.set_title('Error by Channel', color='white', fontsize=12, fontweight='bold')
    ax.set_ylabel('Absolute Error', color='white', fontsize=10)
    ax.tick_params(colors='white')
    for s in ['bottom','left']: ax.spines[s].set_color('white')
    for s in ['top','right']: ax.spines[s].set_visible(False)
    
    fig.suptitle(title, color='#00d4ff', fontsize=15, fontweight='bold', y=1.02)
    plt.tight_layout()
    plt.savefig(save_path, bbox_inches='tight', facecolor=fig.get_facecolor(),
                edgecolor='none', pad_inches=0.3)
    plt.close(fig)


def create_zoom_comparison(original, exact, approx_raw, approx_comp, 
                           crop_region, title, save_path):
    """Zoomed-in crop showing fine detail differences."""
    y1, y2, x1, x2 = crop_region
    
    crops = [
        ("Original", original[y1:y2, x1:x2]),
        ("Exact", exact[y1:y2, x1:x2]),
        ("ALEX Raw", approx_raw[y1:y2, x1:x2]),
        ("ALEX Compensated", approx_comp[y1:y2, x1:x2]),
    ]
    
    fig, axes = plt.subplots(2, 4, figsize=(20, 11), dpi=150,
                              gridspec_kw={'height_ratios': [3, 1]})
    fig.patch.set_facecolor('#1a1a2e')
    
    # Top row: full image with zoom box
    for i, (label, crop) in enumerate(crops):
        ax = axes[0, i]
        # Show full image
        if i == 0: full = original
        elif i == 1: full = exact
        elif i == 2: full = approx_raw
        else: full = approx_comp
        ax.imshow(full)
        # Draw zoom rectangle
        rect = patches.Rectangle((x1, y1), x2-x1, y2-y1, linewidth=2,
                                  edgecolor='#00d4ff', facecolor='none', linestyle='--')
        ax.add_patch(rect)
        ax.set_title(label, color='white', fontsize=11, fontweight='bold')
        ax.axis('off')
    
    # Bottom row: zoomed crops
    for i, (label, crop) in enumerate(crops):
        ax = axes[1, i]
        ax.imshow(crop, interpolation='nearest')
        psnr_val = ""
        if i >= 2:
            p = compute_psnr(crops[1][1], crop)  # vs exact crop
            s = compute_ssim(crops[1][1][:,:,0], crop[:,:,0])  # luma SSIM
            psnr_val = f"\nPSNR={p:.1f}dB"
        ax.set_title(f"Zoomed {label}{psnr_val}", color='#00d4ff', fontsize=9, fontweight='bold')
        ax.axis('off')
    
    fig.suptitle(title, color='#00d4ff', fontsize=14, fontweight='bold', y=1.01)
    plt.tight_layout()
    plt.savefig(save_path, bbox_inches='tight', facecolor=fig.get_facecolor(),
                edgecolor='none', pad_inches=0.3)
    plt.close(fig)


def create_animated_gif(exact, approx_raw, approx_comp, title, save_path):
    """Create an animated GIF cycling through Exact -> Raw -> Compensated."""
    frames = []
    
    labels = [
        ("EXACT Multiplier", exact, "#00ff88"),
        ("ALEX Approximate (Raw)", approx_raw, "#ff6b6b"),
        ("ALEX Bias-Compensated", approx_comp, "#00d4ff"),
    ]
    
    for label_text, img_data, color in labels:
        # Create frame with label overlay
        pil_img = Image.fromarray(img_data)
        draw = ImageDraw.Draw(pil_img)
        
        # Add label bar at top
        bar_height = 36
        draw.rectangle([0, 0, pil_img.width, bar_height], fill=(20, 20, 40, 220))
        
        # Draw text (use default font)
        try:
            font = ImageFont.truetype("arial.ttf", 20)
        except:
            font = ImageFont.load_default()
        
        draw.text((10, 8), label_text, fill=color, font=font)
        
        # Add border glow effect matching the color
        r, g, b = int(color[1:3],16), int(color[3:5],16), int(color[5:7],16)
        for edge in range(3):
            draw.rectangle([edge, edge, pil_img.width-1-edge, pil_img.height-1-edge],
                          outline=(r, g, b, 180-edge*50))
        
        frames.append(pil_img)
    
    # Duplicate frames for pause effect
    extended = []
    for f in frames:
        extended.extend([f] * 2)  # 2 copies = longer pause
    
    extended[0].save(save_path, save_all=True, append_images=extended[1:],
                     duration=800, loop=0, optimize=True)


def create_color_comparison_panel(original, exact, approx_raw, approx_comp,
                                   kernel_name, desc, save_path):
    """Full color comparison: 4 panels + metrics."""
    fig = plt.figure(figsize=(22, 6.5), dpi=150)
    fig.patch.set_facecolor('#1a1a2e')
    gs = GridSpec(1, 5, width_ratios=[1,1,1,1,0.05], wspace=0.06)
    
    panels = [
        ("Original", original),
        ("Exact Multiplier", exact),
        ("ALEX Approx (Raw)", approx_raw),
        ("ALEX Bias-Compensated", approx_comp),
    ]
    
    for i, (title, data) in enumerate(panels):
        ax = fig.add_subplot(gs[0, i])
        ax.imshow(data)
        ax.set_title(title, color='white', fontsize=11, fontweight='bold', pad=6)
        ax.axis('off')
    
    # Error bar in last slot
    ax = fig.add_subplot(gs[0, 4])
    ax.set_facecolor('#16213e')
    error_raw = np.sqrt(np.mean((exact.astype(float)-approx_raw.astype(float))**2, axis=2))
    error_comp = np.sqrt(np.mean((exact.astype(float)-approx_comp.astype(float))**2, axis=2))
    
    # Compute metrics
    psnr_r = compute_psnr(exact, approx_raw)
    ssim_r = np.mean([compute_ssim(exact[:,:,c], approx_raw[:,:,c]) for c in range(3)])
    psnr_c = compute_psnr(exact, approx_comp)
    ssim_c = np.mean([compute_ssim(exact[:,:,c], approx_comp[:,:,c]) for c in range(3)])
    
    metrics_text = (f"RAW\n"
                    f"PSNR: {psnr_r:.1f}dB\n"
                    f"SSIM: {ssim_r:.4f}\n"
                    f"Mean Err: {error_raw.mean():.1f}\n\n"
                    f"COMPENSATED\n"
                    f"PSNR: {psnr_c:.1f}dB\n"
                    f"SSIM: {ssim_c:.4f}\n"
                    f"Mean Err: {error_comp.mean():.1f}")
    ax.text(0.5, 0.5, metrics_text, transform=ax.transAxes, fontsize=8,
            color='white', ha='center', va='center', family='monospace',
            bbox=dict(boxstyle='round', facecolor='#16213e', edgecolor='#00d4ff', alpha=0.9))
    ax.axis('off')
    
    fig.suptitle(f"{kernel_name} -- {desc} (Color, {IMG_SIZE}x{IMG_SIZE})",
                 color='#00d4ff', fontsize=13, fontweight='bold', y=1.01)
    
    plt.savefig(save_path, bbox_inches='tight', facecolor=fig.get_facecolor(),
                edgecolor='none', pad_inches=0.3)
    plt.close(fig)
    
    return {"psnr_raw": psnr_r, "ssim_raw": ssim_r, "psnr_comp": psnr_c, "ssim_comp": ssim_c}


def create_mega_montage(original, all_results, label, save_path):
    """Publication-quality montage of all kernel results on one page."""
    n_kernels = len(all_results)
    fig, axes = plt.subplots(n_kernels, 4, figsize=(20, 5*n_kernels), dpi=120)
    fig.patch.set_facecolor('#1a1a2e')
    
    col_titles = ["Original", "Exact Multiplier", "ALEX Raw", "ALEX Compensated"]
    
    for j, ct in enumerate(col_titles):
        axes[0, j].set_title(ct, color='white', fontsize=12, fontweight='bold', pad=10)
    
    for i, (kname, data) in enumerate(all_results.items()):
        axes[i, 0].imshow(original)
        axes[i, 0].set_ylabel(kname, color='#00d4ff', fontsize=10, fontweight='bold', rotation=0,
                               labelpad=120, va='center')
        axes[i, 1].imshow(data["exact"])
        axes[i, 2].imshow(data["raw"])
        axes[i, 3].imshow(data["comp"])
        
        for j in range(4):
            axes[i, j].axis('off')
        
        # Metrics annotation on compensated panel
        m = data["metrics"]
        axes[i, 3].text(0.98, 0.02,
                        f"PSNR={m['psnr_comp']:.1f}dB\nSSIM={m['ssim_comp']:.3f}",
                        transform=axes[i, 3].transAxes, fontsize=8, color='#00d4ff',
                        ha='right', va='bottom', family='monospace',
                        bbox=dict(boxstyle='round', facecolor='black', alpha=0.7))
    
    fig.suptitle(f"ALEX Multiplier -- All Kernels on {label} (Color {IMG_SIZE}x{IMG_SIZE})",
                 color='#00d4ff', fontsize=16, fontweight='bold', y=1.005)
    plt.tight_layout()
    plt.savefig(save_path, bbox_inches='tight', facecolor=fig.get_facecolor(),
                edgecolor='none', pad_inches=0.5)
    plt.close(fig)


# --- Main ---
def main():
    base_dir = os.path.dirname(os.path.dirname(__file__))
    images = [
        (os.path.join(base_dir, "WhatsApp Image 2026-04-22 at 1.38.19 AM.jpeg"), "Photo1"),
        (os.path.join(base_dir, "WhatsApp Image 2026-04-22 at 1.38.32 AM.jpeg"), "Photo2"),
    ]
    
    for img_path, label in images:
        if not os.path.exists(img_path):
            print(f"SKIP: {img_path}")
            continue
        
        print(f"\n{'='*70}")
        print(f"  COLOR PROCESSING: {label}")
        print(f"  Resolution: {IMG_SIZE}x{IMG_SIZE}, 3 channels (RGB)")
        print(f"{'='*70}")
        
        # Load and resize as COLOR
        original = np.array(Image.open(img_path).convert('RGB').resize(
            (IMG_SIZE, IMG_SIZE), Image.LANCZOS))
        Image.fromarray(original).save(os.path.join(RESULTS_DIR, f"{label}_original_color.png"))
        print(f"  Loaded: {original.shape}, range [{original.min()}, {original.max()}]")
        
        all_kernel_results = {}
        
        for kernel_name, kinfo in KERNELS.items():
            coeffs  = kinfo["coeffs"]
            signs   = kinfo["signs"]
            divisor = kinfo["divisor"]
            desc    = kinfo["desc"]
            
            print(f"\n  [{kernel_name}] {desc}  (3 channels)...")
            t0 = time.time()
            
            exact_rgb = convolve_color(original, coeffs, signs, divisor, mult_exact)
            raw_rgb   = convolve_color(original, coeffs, signs, divisor, mult_approx_raw)
            comp_rgb  = convolve_color(original, coeffs, signs, divisor, mult_approx_comp)
            
            elapsed = time.time() - t0
            safe = kernel_name.replace(" ","_").replace(".","")
            
            # 1) Color comparison panel
            metrics = create_color_comparison_panel(
                original, exact_rgb, raw_rgb, comp_rgb, kernel_name, desc,
                os.path.join(RESULTS_DIR, f"{label}_{safe}_color.png"))
            print(f"    PSNR Raw={metrics['psnr_raw']:.1f}dB  Comp={metrics['psnr_comp']:.1f}dB  ({elapsed:.1f}s)")
            print(f"    -> {label}_{safe}_color.png")
            
            # 2) Diagonal split view
            create_diagonal_split(exact_rgb, raw_rgb,
                f"{label}: {kernel_name} -- Exact vs ALEX Raw",
                os.path.join(RESULTS_DIR, f"{label}_{safe}_split.png"))
            print(f"    -> {label}_{safe}_split.png")
            
            # 3) Error overlay (for non-edge kernels)
            if kinfo["type"] != "edge":
                create_error_overlay(original, exact_rgb, raw_rgb,
                    f"{label}: {kernel_name} Error Analysis",
                    os.path.join(RESULTS_DIR, f"{label}_{safe}_error_overlay.png"))
                print(f"    -> {label}_{safe}_error_overlay.png")
            
            # 4) Animated GIF
            create_animated_gif(exact_rgb, raw_rgb, comp_rgb,
                f"{kernel_name}",
                os.path.join(RESULTS_DIR, f"{label}_{safe}_animated.gif"))
            print(f"    -> {label}_{safe}_animated.gif")
            
            # Store for montage
            all_kernel_results[kernel_name] = {
                "exact": exact_rgb, "raw": raw_rgb, "comp": comp_rgb, "metrics": metrics
            }
        
        # 5) Zoomed crop (face region -- approximate center of the photos)
        # Photo is a portrait, face is roughly in center-upper region
        cy, cx = IMG_SIZE//3, IMG_SIZE//2
        crop_size = IMG_SIZE // 4
        crop_region = (cy-crop_size//2, cy+crop_size//2, cx-crop_size//2, cx+crop_size//2)
        
        # Use brightness x1.3 for zoom (best approx performance)
        br_key = "Brightness x1.3"
        if br_key in all_kernel_results:
            create_zoom_comparison(
                original, all_kernel_results[br_key]["exact"],
                all_kernel_results[br_key]["raw"], all_kernel_results[br_key]["comp"],
                crop_region, f"{label}: Brightness x1.3 -- Face Detail Zoom",
                os.path.join(RESULTS_DIR, f"{label}_zoom_brightness.png"))
            print(f"\n    -> {label}_zoom_brightness.png")
        
        # Also zoom on Gaussian compensated
        gauss_key = "Gaussian Blur 5x5"
        if gauss_key in all_kernel_results:
            create_zoom_comparison(
                original, all_kernel_results[gauss_key]["exact"],
                all_kernel_results[gauss_key]["raw"], all_kernel_results[gauss_key]["comp"],
                crop_region, f"{label}: Gaussian 5x5 -- Face Detail Zoom",
                os.path.join(RESULTS_DIR, f"{label}_zoom_gaussian.png"))
            print(f"    -> {label}_zoom_gaussian.png")
        
        # 6) Mega montage
        print(f"\n  Generating mega montage for {label}...")
        create_mega_montage(original, all_kernel_results, label,
                            os.path.join(RESULTS_DIR, f"{label}_mega_montage.png"))
        print(f"    -> {label}_mega_montage.png")
    
    # --- Combined summary ---
    print(f"\n{'='*70}")
    print(f"  All results: {os.path.abspath(RESULTS_DIR)}")
    print(f"{'='*70}")


if __name__ == "__main__":
    main()
