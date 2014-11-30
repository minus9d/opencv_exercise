# -*- coding: utf-8 -*-

import cv2
import numpy as np
import matplotlib.pyplot as plt
import timeit

print cv2.__version__

def print_image_info():
    #img = cv2.imread('../img/board.jpg', cv2.IMREAD_COLOR)
    img = cv2.imread('../img/board.jpg', cv2.IMREAD_GRAYSCALE)

    print(img.shape)

    # 行数
    print("rows = ", img.shape[0])
    # 列数
    print("cols = ", img.shape[1])

    # 次元数
    # cv::Matではdimensionとchannelを区別するが、pythonでは区別しない。
    # そのため1対1に対応しない
    print("dims(?) = ", len(img.shape))

    # サイズ（2次元の場合）
    # Pythonではcv::Sizeに対応するものはない

    # ビット深度みたいなもの
    # 自信なし
    print("depth(?) = ", img.dtype)

    # チャンネル数
    # pythonでは次元とチャネルの区別がない
    #std::cout << "channels: " << img.channels() << std::endl;

    ## （複数チャンネルから成る）1要素のサイズ [バイト単位]
    #std::cout << "elemSize: " << img.elemSize() << "[byte]" << std::endl;

    ## 1要素内の1チャンネル分のサイズ [バイト単位]
    #std::cout << "elemSize1 (elemSize/channels): " << img.elemSize1() << "[byte]" << std::endl;

    ## タイプ
    #std::cout << "type (ID): " << img.type() << "(=" << CV_8UC3 << ")" << std::endl;

    ## 要素の総数
    #std::cout << "total: " << img.total() << std::endl;
    ## ステップ数 [バイト単位]
    #std::cout << "step: " << img.step << "[byte]" << std::endl;
    ## 1ステップ内のチャンネル総数
    #std::cout << "step1 (step/elemSize1): " << img.step1() << std::endl;
    ## データは連続か？
    #std::cout << "isContinuous: " << (img.isContinuous() ? "true" : "false") << std::endl;
    ## 部分行列か？
    #std::cout << "isSubmatrix: " << (img.isSubmatrix() ? "true" : "false") << std::endl;
    ## データは空か？
    #std::cout << "empty: " << (img.empty() ? "true" : "false") << std::endl;



def basic():
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

    print("test")
    print(img_color.shape[2])

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
    print img_color[20, 100, 0]
    print img_color[20, 100, 1]
    print img_color[20, 100, 2]

    # いろんなスライス
    print img_color[20]
    print img_color[:, 20, :]

    ## 部分画像
    #img_roi = img_color[50:100, 100:200]
    #cv2.imshow("roi", img_roi)

    # 新しい空の画像生成
    new_image = np.zeros( img_color.shape, np.uint8)

    # 部分に色を塗る
    new_image[50:100, 200:300] = (255, 0, 0)
    cv2.imshow("empty image", new_image)
    cv2.waitKey(1)

print_image_info()
basic()
