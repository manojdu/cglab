import cv2  # Import the OpenCV library for image processing
import numpy as np  # Import NumPy for numerical operations
import matplotlib.pyplot as plt  # Import Matplotlib for displaying images

# Load the image in grayscale mode
img = cv2.imread("sde.jpeg", cv2.IMREAD_GRAYSCALE)  # Read the image in grayscale
image_array = np.array(img)  # Convert the image to a NumPy array
print(image_array)  # Print the image array to the console

# Define a sharpening kernel
def sharpen():
    """
    Function to return a sharpening kernel.
    
    Returns:
    numpy.ndarray: Sharpening kernel
    """
    return np.array([[1, 1, 1], [1, 1, 1], [1, 1, 1]])  # Define a 3x3 kernel filled with ones

# Define a filtering function
def filtering(image, kernel):
    """
    Function to apply a kernel filter to an image.
    
    Parameters:
    image (numpy.ndarray): Input image
    kernel (numpy.ndarray): Kernel for filtering
    
    Returns:
    numpy.ndarray: Filtered image
    """
    m, n = kernel.shape  # Get the shape of the kernel
    if m == n:  # Ensure the kernel is square
        y, x = image.shape  # Get the shape of the image
        y = y - m + 1  # Calculate the height of the new image
        x = x - m + 1  # Calculate the width of the new image
        new_image = np.zeros((y, x))  # Initialize the new image with zeros
        for i in range(y):
            for j in range(x):
                new_image[i][j] = np.sum(image[i:i+m, j:j+m] * kernel)  # Apply the kernel to the image region
    return new_image  # Return the filtered image

# Display the original and sharpened images
plt.figure(figsize=(10, 5))  # Create a figure with a specified size

# Display the original grayscale image
plt.subplot(1, 2, 1)  # Create a subplot in the 1st row, 2nd column, 1st position
plt.imshow(image_array, cmap='gray')  # Display the original grayscale image
plt.title("Original Grayscale Image")  # Set the title for the subplot
plt.axis("off")  # Turn off the axis

# Display the filtered image
plt.subplot(1, 2, 2)  # Create a subplot in the 1st row, 2nd column, 2nd position
plt.imshow(filtering(image_array, sharpen()), cmap='gray')  # Display the filtered image
plt.title("Blurred Image")  # Set the title for the subplot
plt.axis("off")  # Turn off the axis

# Show the plots
plt.show()  # Display all the subplots
