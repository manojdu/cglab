import cv2  # Import the OpenCV library for image processing
import numpy as np  # Import NumPy for numerical operations

def translate_image(image, dx, dy):
    """
    Function to translate an image by dx and dy pixels.
    
    Parameters:
    image (numpy.ndarray): Input image
    dx (int): Translation in the x-direction
    dy (int): Translation in the y-direction
    
    Returns:
    numpy.ndarray: Translated image
    """
    rows, cols = image.shape[:2]  # Get the number of rows and columns in the image
    translation_matrix = np.float32([[1, 0, dx], [0, 1, dy]])  # Create the translation matrix
    translated_image = cv2.warpAffine(image, translation_matrix, (cols, rows))  # Apply the translation
    return translated_image  # Return the translated image

# Read the image
image = cv2.imread('sde.jpeg')  # Read the image from the specified path

# Get image dimensions
height, width = image.shape[:2]  # Extract the height and width of the image

# Calculate the center coordinates of the image
center = (width // 2, height // 2)  # Calculate the center of the image

# Get rotation and scaling values from the user
rotation_value = int(input("Enter the degree of Rotation:"))  # Prompt user for rotation degree
scaling_value = int(input("Enter the zooming factor:"))  # Prompt user for scaling factor

# Create the 2D rotation matrix for rotation
rotated = cv2.getRotationMatrix2D(center=center, angle=rotation_value, scale=1)  # Create rotation matrix
rotated_image = cv2.warpAffine(src=image, M=rotated, dsize=(width, height))  # Apply rotation to the image

# Create the 2D rotation matrix for scaling
scaled = cv2.getRotationMatrix2D(center=center, angle=0, scale=scaling_value)  # Create scaling matrix
scaled_image = cv2.warpAffine(src=rotated_image, M=scaled, dsize=(width, height))  # Apply scaling to the rotated image

# Get translation values from the user
h = int(input("How many pixels do you want the image to be translated horizontally? "))  # Prompt user for horizontal translation
v = int(input("How many pixels do you want the image to be translated vertically? "))  # Prompt user for vertical translation

# Apply translation to the scaled image
translated_image = translate_image(scaled_image, dx=h, dy=v)  # Translate the scaled image

# Save the final image
cv2.imwrite('Final_image.png', translated_image)  # Save the final translated image
