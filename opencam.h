#ifndef OPENCAM_H
#define OPENCAM_H

#include <QWidget>
#include <QImage>
#include <QTimer>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <imgproc/imgproc.hpp>
#include <img_filter.h>

using namespace cv;
using namespace std;

namespace Ui {
class opencam;
}

class opencam : public QWidget
{
    Q_OBJECT

public:
    explicit opencam(QWidget *parent = 0);
    ~opencam();

private slots:
    void openCamera();      // 打开摄像头
    void readFarme();       // 读取当前帧
    void closeCamera();     // 关闭摄像头
    void takingPictures();  // 拍照


private:
    Ui::opencam *ui;
    QImage Mat2QImage(Mat cvImg);
    QTimer    *timer;
    QImage    *imag;
    VideoCapture cap;//视频获取结构，用来作为视频获取函数的一个参数
    Mat frame;//Mat类型，每一帧存放地址
};

#endif // OPENCAM_H
