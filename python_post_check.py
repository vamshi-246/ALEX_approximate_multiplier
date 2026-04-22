import numpy as np

def compute_psnr(ref, test, max_val):
    mse = np.mean((ref - test) ** 2)

    if mse == 0:
        return float('inf')  # perfect match

    psnr = 10 * np.log10((max_val ** 2) / mse)
    return psnr


def run_analysis(fileA, fileB, fileRTL):
    # Load inputs
    A = np.loadtxt(fileA, dtype=np.float32)
    B = np.loadtxt(fileB, dtype=np.float32)
    RTL = np.loadtxt(fileRTL, dtype=np.float32)

    # Compute reference
    REF = A * B

    # Flatten safety (in case shapes mismatch)
    A = A.flatten()
    B = B.flatten()
    REF = REF.flatten()
    RTL = RTL.flatten()

    assert len(REF) == len(RTL), "Size mismatch!"

    # Metrics
    mae = np.mean(np.abs(REF - RTL))
    max_err = np.max(np.abs(REF - RTL))
    psnr = compute_psnr(REF, RTL, max_val=65535)  # 16-bit range

    print("========== RESULTS ==========")
    print(f"MAE      : {mae:.4f}")
    print(f"MAX ERROR: {max_err}")
    print(f"PSNR     : {psnr:.2f} dB")


# =============================
# RUN
# =============================
run_analysis("cameraman.txt", "circle.txt", "cameramanxcircle.txt")