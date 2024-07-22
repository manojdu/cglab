import cv2  # Import the OpenCV library for image processing
import numpy as np  # Import NumPy for numerical operations

# Specify the path to the image file
image_path = 'sde.jpeg'  # Path to the input image
image = cv2.imread(image_path)  # Read the image from the specified path

# Convert the image to grayscale (contours work best on binary images)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)  # Convert the image from BGR to grayscale

# Apply thresholding (you can use other techniques like Sobel edges)
_, binary_image = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)  # Apply binary thresholding

# Find contours
contours, _ = cv2.findContours(binary_image, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)  # Find contours in the binary image

# Draw all contours on the original image
cv2.drawContours(image, contours, -1, (0, 255, 0), 3)  # Draw the contours on the original image in green color with thickness 3

# Display the result
cv2.imshow('Contours', image)  # Display the image with contours
cv2.waitKey(0)  # Wait indefinitely for a key press
cv2.destroyAllWindows()  # Close all OpenCV windows
