import cv2
import cvlib as cv
from cvlib.object_detection import draw_bbox

# open webcam
webcam = cv2.VideoCapture(0)

while True:
    ret, frame = webcam.read()
    bbox, label, conf = cv.detect_common_objects(frame)
    out = draw_bbox(frame, bbox, label, conf)

    cv2.imshow("Real-time object detection", out)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
