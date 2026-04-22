from PIL import Image
import numpy as np

def txt_stream_to_image(input_txt, output_image, size=(512,512)):
    h, w = size

    # Read values
    with open(input_txt, 'r') as f:
        data = [int(line.strip()) for line in f]

    arr = np.array(data, dtype=np.float32).reshape((h, w))

    # Normalize to 0–255
    arr = arr - arr.min()
    arr = arr / arr.max() * 255.0

    arr = arr.astype(np.uint8)

    img = Image.fromarray(arr, mode='L')
    img.save(output_image)

    print("Saved normalized image")

# usage
txt_stream_to_image("cameramanxcircle.txt", "cameramanxcircle.png")