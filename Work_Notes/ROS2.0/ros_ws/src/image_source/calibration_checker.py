#!/usr/bin/env python

import os
import json
import numpy as np
import cv2

# Usage: Set the warning area polygon in the parameter json file and run ./calibration_checker.py

def checkerboard_overlay():
    current_dir = os.path.dirname(os.path.realpath(__file__))
    json_file = os.path.join(current_dir, "config/basler_camera.json")
    with open(json_file) as f:
        params = json.load(f)

    pts = np.array(params["warning_area"], np.int32)
    pts = pts.reshape((-1,1,2))

    cap = cv2.VideoCapture(0)
    if not cap.isOpened():
        raise Exception("Could not open video device")
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, params["image_width"])
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, params["image_height"])

    cv2.namedWindow("Camera orientation")
    while True:
        ret, frame = cap.read()
        if not ret:
            break

        cv2.polylines(frame, [pts], True, (0,255,255))
        cv2.imshow("Camera orientation", frame)

        k = cv2.waitKey(1)

        if k%256 == 27:
            # ESC pressed
            print("Escape it, closing...")
            break
    
    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    try:
        checkerboard_overlay()
    except KeyboardInterrupt:
        pass
