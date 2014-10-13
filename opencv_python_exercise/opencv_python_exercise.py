# -*- coding: utf-8 -*-

import cv2
import numpy as np
import matplotlib.pyplot as plt

print cv2.__version__

# 画像読み込みと表示
img_color = cv2.imread('../img/board.jpg', cv2.IMREAD_COLOR)
img_gray = cv2.imread('../img/board.jpg', cv2.CV_LOAD_IMAGE_GRAYSCALE)

if img_color is not None:
    cv2.imshow("img", img_color)

height, width, depth = img_color.shape
print img_color.shape
height, width = img_gray.shape
dtype = img_color.dtype
img_size = img_color.size



# 画像のクローン
# ?? img = img_color.clone()

# 画像を白黒に変換
img_gray = cv2.cvtColor(img_color, cv2.COLOR_BGR2GRAY)

# 画像の保存
cv2.imwrite('out.jpg', img_gray)

# b, g, rに分解
b, g, r = cv2.split(img_color)
# 順番を入れ替えて結合
img_rgb = cv2.merge([r,g,b])

# 画像の表示(matplotlibを使う)
#plt.imshow(img_gray, cmap = plt.get_cmap('gray'))  # 白黒
#plt.imshow(img_rgb)
#plt.xticks([]), plt.yticks([])  # to hide tick values on X and Y axis
#plt.show()

# 画素へのアクセス
print img_color[20, 100]  # y座標, x座標の順番

# 部分画像
img_roi = img_color[50:100, 100:200]
cv2.imshow("roi", img_roi)



cv2.waitKey()

