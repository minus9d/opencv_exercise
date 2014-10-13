print('Hello World')

import cv2

print cv2.__version__

img_color = cv2.imread('../img/board.jpg')
img_gray = cv2.imread('../img/board.jpg', cv2.CV_LOAD_IMAGE_GRAYSCALE)

if img_color is not None:
    cv2.imshow("img", img_color)

cv2.waitKey()

