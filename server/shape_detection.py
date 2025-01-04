import cv2
import numpy as np

# Load the image
image = cv2.imread('./shape.jpg')

# Convert to grayscale
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Apply edge detection or thresholding to highlight shapes
edges = cv2.Canny(gray, 50, 150)

# Find contours in the edge-detected image
contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Iterate over contours
for contour in contours:
    # Approximate the contour to reduce the number of points
    epsilon = 0.03 * cv2.arcLength(contour, True)
    approx = cv2.approxPolyDP(contour, epsilon, True)

    # Look for cross-shaped contours: they generally have 12-14 vertices or two intersecting lines
    if 10 <= len(approx) <= 14:  # Adjust based on your needs
        # Get the bounding box and aspect ratio of the contour
        x, y, w, h = cv2.boundingRect(contour)
        aspect_ratio = float(w) / h

        # Check aspect ratio to differentiate between crosses and other shapes
        if 0.8 < aspect_ratio < 1.2:
            # Further filter based on shape characteristics
            # Draw the contour on the original image
            cv2.drawContours(image, [approx], -1, (0, 255, 0), 3)
            cv2.putText(image, "Cross", (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

# Display the result
cv2.imshow("Detected Crosses", image)
cv2.waitKey(0)
cv2.destroyAllWindows()

