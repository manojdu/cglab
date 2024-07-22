import cv2  # Import the OpenCV library for image processing
import numpy as np  # Import NumPy for numerical operations

# Load the image
image_path = "sde.jpeg"  # Replace with the path to your image
img = cv2.imread(image_path)  # Read the image from the specified path

# Convert the image to grayscale
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # Convert the image from BGR to grayscale

# Edge detection
edges = cv2.Canny(gray, 100, 200)  # Use the Canny edge detector on the grayscale image with threshold values 100 and 200

# Texture extraction
kernel = np.ones((5, 5), np.float32) / 25  # Define a 5x5 averaging kernel
texture = cv2.filter2D(gray, -1, kernel)  # Apply the averaging filter to extract texture from the grayscale image

# Display the original image, edges, and texture
cv2.imshow("Original Image", img)  # Display the original image
cv2.imshow("Edges", edges)  # Display the edges detected by the Canny edge detector
cv2.imshow("Texture", texture)  # Display the texture extracted by the averaging filter

# Wait for a key press and then close all windows
cv2.waitKey(0)  # Wait indefinitely for a key press
cv2.destroyAllWindows()  # Close all OpenCV windows
