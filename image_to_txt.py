from PIL import Image
import numpy as np

def image_to_txt_stream(input_path, output_txt, size=(256, 256)):
    # Load + grayscale
    img = Image.open(input_path).convert('L')

    # Resize
    img = img.resize(size, Image.BILINEAR)

    # Convert to array
    arr = np.array(img, dtype=np.uint8)

    h, w = arr.shape

    # Write in required order: m[i][j] → one per line
    with open(output_txt, 'w') as f:
        for i in range(h):
            for j in range(w):
                f.write(f"{arr[i][j]}\n")

    print(f"Saved stream format to {output_txt} ({h*w} values)")

# Example
image_to_txt_stream("cameraman.png", "cameraman.txt")