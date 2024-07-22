import cv2
import numpy as np
import matplotlib.pyplot as plt

# Read the image
image_path = 'sde.jpeg'  # Specify the path to your image file
img = cv2.imread(image_path)

# Get the height and width of the image
height, width = img.shape[:2]

# Split the image into four quadrants
quad1 = img[:height//2, :width//2]   # Top-left quadrant
quad2 = img[:height//2, width//2:]   # Top-right quadrant
quad3 = img[height//2:, :width//2]   # Bottom-left quadrant
quad4 = img[height//2:, width//2:]   # Bottom-right quadrant

# Create a figure for displaying the first two quadrants
plt.figure(figsize=(10, 5))

# Display the first quadrant
plt.subplot(1, 2, 1)               # Create a subplot in the 1st row, 2nd column, 1st position
plt.imshow(cv2.cvtColor(quad1, cv2.COLOR_BGR2RGB))  # Convert color from BGR to RGB for displaying
plt.title("1")                     # Set the title for the subplot
plt.axis("off")                    # Turn off the axis

# Display the second quadrant
plt.subplot(1, 2, 2)               # Create a subplot in the 1st row, 2nd column, 2nd position
plt.imshow(cv2.cvtColor(quad2, cv2.COLOR_BGR2RGB))  # Convert color from BGR to RGB for displaying
plt.title("2")                     # Set the title for the subplot
plt.axis("off")                    # Turn off the axis

# Create a figure for displaying the last two quadrants
plt.figure(figsize=(10, 5))

# Display the third quadrant
plt.subplot(1, 2, 1)               # Create a subplot in the 1st row, 2nd column, 1st position
plt.imshow(cv2.cvtColor(quad3, cv2.COLOR_BGR2RGB))  # Convert color from BGR to RGB for displaying
plt.title("3")                     # Set the title for the subplot
plt.axis("off")                    # Turn off the axis

# Display the fourth quadrant
plt.subplot(1, 2, 2)               # Create a subplot in the 1st row, 2nd column, 2nd position
plt.imshow(cv2.cvtColor(quad4, cv2.COLOR_BGR2RGB))  # Convert color from BGR to RGB for displaying
plt.title("4")                     # Set the title for the subplot
plt.axis("off")                    # Turn off the axis

# Show the plots
plt.show()                         # Display all the subplots
