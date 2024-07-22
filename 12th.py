import cv2  # Import the OpenCV library for image processing

# Load the pre-trained Haar Cascade classifiers for face and eye detection
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_eye.xml')

# Read the input image (replace 'face.jpeg' with the path to your image file)
image_path = 'face.jpeg'  # Path to the input image
image = cv2.imread(image_path)  # Read the image from the specified path

# Convert the image to grayscale
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)  # Convert the image from BGR to grayscale for better detection

# Detect faces in the grayscale image
faces = face_cascade.detectMultiScale(gray, scaleFactor=1.3, minNeighbors=5)
# 'scaleFactor' compensates for faces appearing at different sizes
# 'minNeighbors' specifies how many neighbors each candidate rectangle should have to retain it

# Draw rectangles around detected faces
for (x, y, w, h) in faces:
    cv2.rectangle(image, (x, y), (x + w, y + h), (255, 0, 0), 2)
    # Draw a rectangle around each detected face
    # (x, y) is the top-left corner of the rectangle
    # (x + w, y + h) is the bottom-right corner
    # (255, 0, 0) specifies the color of the rectangle (red in BGR format)
    # 2 specifies the thickness of the rectangle's border

# Save or display the result
cv2.imwrite('detected_faces.jpg', image)  # Save the image with detected faces to a file
cv2.imshow('Detected Faces', image)  # Display the image with detected faces in a window
cv2.waitKey(0)  # Wait indefinitely for a key press
cv2.destroyAllWindows()  # Close all OpenCV windows
