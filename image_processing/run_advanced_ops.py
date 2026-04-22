"""
Advanced Image Operations with ALEX Multiplier
Demonstrates architectural optimizations:
1. Separable Convolution (1D passes instead of 2D grids)
2. Coefficient-Aware Bias Compensation
3. Low-multiplication ops (Alpha Blending, Motion Blur)
"""

import os, sys, time
import numpy as np
from PIL import Image
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.gridspec import GridSpec

from alex_multiplier_model import build_approx_lut, build_exact_lut

# --- Setup ---
RESULTS_DIR = os.path.join(os.path.dirname(__file__), "results_advanced")
os.makedirs(RESULTS_DIR, exist_ok=True)
IMG_SIZE = 512

print("Building lookup tables...")
APPROX_LUT = build_approx_lut()
EXACT_LUT  = build_exact_lut()

# Calculate specific bias for each possible 8-bit coefficient (0-255)
# This is much more accurate than a single global mean!
COEFF_BIAS = np.zeros(256, dtype=np.int32)
for coeff in range(256):
    exact_vals = EXACT_LUT[:, coeff].astype(np.int32)
    approx_vals = APPROX_LUT[:, coeff].astype(np.int32)
    COEFF_BIAS[coeff] = int(round(np.mean(approx_vals - exact_vals)))

# --- Multipliers ---
def mult_exact(a, b):
    return EXACT_LUT[a.astype(np.uint8), b.astype(np.uint8)].astype(np.int32)

def mult_approx_raw(a, b):
    return APPROX_LUT[a.astype(np.uint8), b.astype(np.uint8)].astype(np.int32)

def mult_approx_comp_aware(a, b):
    a8, b8 = a.astype(np.uint8), b.astype(np.uint8)
    raw_val = APPROX_LUT[a8, b8].astype(np.int32)
    # Get the specific bias for coefficient b8
    # Since b is a constant array in convolution, we take b8[0,0]
    bias = COEFF_BIAS[b8.flatten()[0]] 
    return raw_val - bias


# --- Metrics ---
def compute_metrics(ref, test):
    mse = np.mean((ref.astype(np.float64) - test.astype(np.float64)) ** 2)
    psnr = 10.0 * np.log10(255.0**2 / mse) if mse > 1e-10 else float('inf')
    
    # Simple SSIM
    r, t = ref.astype(np.float64), test.astype(np.float64)
    C1, C2 = (0.01*255)**2, (0.03*255)**2
    mu_x, mu_y = np.mean(r), np.mean(t)
    sig_x2, sig_y2 = np.var(r), np.var(t)
    sig_xy = np.mean((r - mu_x) * (t - mu_y))
    ssim = ((2*mu_x*mu_y+C1)*(2*sig_xy+C2)) / ((mu_x**2+mu_y**2+C1)*(sig_x2+sig_y2+C2))
    return psnr, ssim

# --- 1D/2D Convolution ---
def convolve_1d(image, kernel, divisor, mult_fn, axis):
    """1D convolution along specified axis (0=vertical, 1=horizontal)"""
    h, w = image.shape
    k_len = len(kernel)
    pad = k_len // 2
    
    if axis == 1:
        padded = np.pad(image, ((0,0), (pad,pad)), mode='edge')
        output = np.zeros_like(image, dtype=np.float64)
        for i in range(k_len):
            coeff = int(kernel[i])
            if coeff == 0: continue
            window = padded[:, i:i+w].astype(np.uint8)
            coeff_arr = np.full_like(window, coeff)
            output += mult_fn(window, coeff_arr)
    else:
        padded = np.pad(image, ((pad,pad), (0,0)), mode='edge')
        output = np.zeros_like(image, dtype=np.float64)
        for i in range(k_len):
            coeff = int(kernel[i])
            if coeff == 0: continue
            window = padded[i:i+h, :].astype(np.uint8)
            coeff_arr = np.full_like(window, coeff)
            output += mult_fn(window, coeff_arr)
            
    return output / divisor if divisor else output

def convolve_separable(image_rgb, kernel_1d, divisor_1d, mult_fn):
    """Applies separable convolution per channel"""
    result = np.zeros_like(image_rgb, dtype=np.float64)
    for c in range(3):
        ch = image_rgb[:,:,c]
        # Horizontal pass
        horiz = convolve_1d(ch, kernel_1d, divisor_1d, mult_fn, axis=1)
        horiz_clip = np.clip(horiz, 0, 255).astype(np.uint8)
        # Vertical pass
        vert = convolve_1d(horiz_clip, kernel_1d, divisor_1d, mult_fn, axis=0)
        result[:,:,c] = vert
    return np.clip(result, 0, 255).astype(np.uint8)

def process_alpha_blend(img1, img2, alpha_weight, mult_fn):
    res = np.zeros_like(img1, dtype=np.float64)
    for c in range(3):
        p1 = mult_fn(img1[:,:,c], np.full_like(img1[:,:,c], alpha_weight))
        p2 = mult_fn(img2[:,:,c], np.full_like(img2[:,:,c], 255 - alpha_weight))
        res[:,:,c] = (p1 + p2) / 255.0
    return np.clip(res, 0, 255).astype(np.uint8)


def create_panel(exact, raw, comp, title, save_path):
    fig = plt.figure(figsize=(15, 5.5), dpi=150)
    fig.patch.set_facecolor('#1a1a2e')
    gs = GridSpec(1, 3, wspace=0.05)
    
    psnr_r, ssim_r = compute_metrics(exact, raw)
    psnr_c, ssim_c = compute_metrics(exact, comp)
    
    panels = [
        ("Exact Multiplier", exact),
        (f"ALEX Raw\nPSNR: {psnr_r:.1f}dB, SSIM: {ssim_r:.3f}", raw),
        (f"ALEX Optimized\nPSNR: {psnr_c:.1f}dB, SSIM: {ssim_c:.3f}", comp)
    ]
    
    for i, (label, data) in enumerate(panels):
        ax = fig.add_subplot(gs[0, i])
        ax.imshow(data)
        ax.set_title(label, color='#00d4ff', fontsize=12, fontweight='bold', pad=10)
        ax.axis('off')
        
    fig.suptitle(title, color='white', fontsize=16, fontweight='bold', y=1.05)
    plt.savefig(save_path, bbox_inches='tight', facecolor=fig.get_facecolor(), pad_inches=0.2)
    plt.close(fig)
    return psnr_r, psnr_c

def main():
    base_dir = os.path.dirname(os.path.dirname(__file__))
    p1_path = os.path.join(base_dir, "WhatsApp Image 2026-04-22 at 1.38.19 AM.jpeg")
    p2_path = os.path.join(base_dir, "WhatsApp Image 2026-04-22 at 1.38.32 AM.jpeg")
    
    img1 = np.array(Image.open(p1_path).convert('RGB').resize((IMG_SIZE, IMG_SIZE), Image.LANCZOS))
    img2 = np.array(Image.open(p2_path).convert('RGB').resize((IMG_SIZE, IMG_SIZE), Image.LANCZOS))
    
    print("\n--- Advanced Image Processing ---")
    
    # 1. Separable Gaussian Blur (1D: [1, 4, 6, 4, 1])
    print("\nRunning Separable Gaussian Blur 5x5...")
    k_gauss_1d = [1, 4, 6, 4, 1]
    div_1d = 16
    
    ex_blur = convolve_separable(img1, k_gauss_1d, div_1d, mult_exact)
    raw_blur = convolve_separable(img1, k_gauss_1d, div_1d, mult_approx_raw)
    comp_blur = convolve_separable(img1, k_gauss_1d, div_1d, mult_approx_comp_aware)
    
    pr, pc = create_panel(ex_blur, raw_blur, comp_blur, 
        "Separable 5x5 Gaussian Blur (10 multiplications/pixel)",
        os.path.join(RESULTS_DIR, "separable_gaussian.png"))
    print(f"PSNR: Raw={pr:.1f}dB -> Optimized={pc:.1f}dB")
    
    # 2. Motion Blur (Horizontal 9-tap)
    print("\nRunning Motion Blur (9-tap directional)...")
    k_motion = [1]*9
    ex_motion = np.zeros_like(img1)
    raw_motion = np.zeros_like(img1)
    comp_motion = np.zeros_like(img1)
    for c in range(3):
        ex_motion[:,:,c] = convolve_1d(img2[:,:,c], k_motion, 9, mult_exact, axis=1)
        raw_motion[:,:,c] = convolve_1d(img2[:,:,c], k_motion, 9, mult_approx_raw, axis=1)
        comp_motion[:,:,c] = convolve_1d(img2[:,:,c], k_motion, 9, mult_approx_comp_aware, axis=1)
        
    pr, pc = create_panel(ex_motion, raw_motion, comp_motion, 
        "Motion Blur (9 multiplications/pixel)",
        os.path.join(RESULTS_DIR, "motion_blur.png"))
    print(f"PSNR: Raw={pr:.1f}dB -> Optimized={pc:.1f}dB")

    # 3. Alpha Blending
    print("\nRunning Alpha Blending (Compositing Photo1 & Photo2)...")
    ex_blend = process_alpha_blend(img1, img2, 128, mult_exact)
    raw_blend = process_alpha_blend(img1, img2, 128, mult_approx_raw)
    comp_blend = process_alpha_blend(img1, img2, 128, mult_approx_comp_aware)
    
    pr, pc = create_panel(ex_blend, raw_blend, comp_blend, 
        "Alpha Blending (2 multiplications/pixel)",
        os.path.join(RESULTS_DIR, "alpha_blend.png"))
    print(f"PSNR: Raw={pr:.1f}dB -> Optimized={pc:.1f}dB")

    print("\nDone! Results saved to results_advanced folder.")

if __name__ == "__main__":
    main()
