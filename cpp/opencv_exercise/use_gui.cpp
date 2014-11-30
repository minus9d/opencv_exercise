/**
    @brief �}�E�X�R�[���o�b�N�̃T���v���v���O�����BOriginal: http://dasl.mem.drexel.edu/~noahKuntz/openCVTut3.html#Step%201
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// �O���[�o���ϐ�
cv::Rect box;
bool drawing_box = false;
int g_switch_value = 0;

void draw_box(cv::Mat* img, cv::Rect rect){
    cv::rectangle(*img, cv::Point2d(box.x, box.y), cv::Point2d(box.x + box.width, box.y + box.height),
        cv::Scalar(0xff, 0x00, 0x00));
}

// �R�[���o�b�N�֐�
void my_mouse_callback(int event, int x, int y, int flags, void* param){
    cv::Mat* image = static_cast<cv::Mat*>(param);

    switch (event){
    case cv::EVENT_MOUSEMOVE:
        if (drawing_box){
            box.width = x - box.x;
            box.height = y - box.y;
        }
        break;

    case cv::EVENT_LBUTTONDOWN:
        drawing_box = true;
        box = cv::Rect(x, y, 0, 0);
        break;

    case cv::EVENT_LBUTTONUP:
        drawing_box = false;
        if (box.width < 0){
            box.x += box.width;
            box.width *= -1;
        }
        if (box.height < 0){
            box.y += box.height;
            box.height *= -1;
        }
        draw_box(image, box);
        break;
    }
}

void switch_callback(int position, void *dummy){
    std::cout  << position << std::endl;
}

int useGUI(void)
{
    std::string name = "Box Example";
    box = cv::Rect(-1, -1, 0, 0);

    // �D�F�̉摜�𐶐�
    cv::Mat image(cv::Size(960, 540), CV_8UC3, cv::Scalar(100, 100, 100));
    cv::Mat temp = image.clone();

    // �E�B���h�E�𐶐�
    cv::namedWindow(name, CV_WINDOW_AUTOSIZE);

    // �R�[���o�b�N��ݒ�
    cv::setMouseCallback(name, my_mouse_callback, (void *)&image);

    cv::createTrackbar("Switch", name, &g_switch_value, 100, switch_callback);

    // Main loop
    while (1){
        // image��temp�ɃR�s�[
        image.copyTo(temp);

        // �}�E�X�̍��N���b�N�𗣂��܂ł̊ԁA��`���ꎞ�I�ɕ`��
        if (drawing_box) {
            draw_box(&temp, box);
        }

        cv::imshow(name, temp);

        // Esc�ŏI��
        if (cv::waitKey(15) == 27)
            break;
    }

    return 0;
}
