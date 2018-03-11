#ifndef OPENCAM_H
#define OPENCAM_H

#include <QWidget>
#include <QImage>
#include <QTimer>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <imgproc/imgproc.hpp>
#include <img_filter.h>
#include <QFileDialog>
#include <QScreen>
#include <QDateTime>
#include <QCloseEvent>
#include <QtConcurrent/QtConcurrent>
#include <QMutex>
#include "util.h"
#include "picinfo.h"
#include "settingdialog.h"
#include "faceprocess.h"
#include "editwindow.h"
using namespace cv;
using namespace std;

namespace Ui {
class Opencam;
}

class Opencam : public QWidget
{
    Q_OBJECT

public:
    explicit Opencam(QWidget *parent = 0);
    ~Opencam();

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void PicinfoSend(PicInfo*);

private slots:
    void OpenCamera();      // 打开摄像头
    void ReadFrame();       // 读取当前帧
    void CloseCamera();     // 关闭摄像头
    void Take_Click();      // 拍照按钮
    void Save_Click();      // 存图片按钮
    void Cancel_Click();    // 取消存图片
    void ZoomIn_Click();    // 放大按钮
    void ZoomOut_Click();   // 缩小按钮
    void Setting_Click();   // 设置按钮
    void SetContinue();     // 设置连拍
    void ShowPic_Click();

private:
    Ui::Opencam *ui;
    QTimer    *timer;
    QImage    *imag;
    PicInfo   *picinfo;

    //跳帧计数器
    int count = 0;
    int threadon = 0;

    VideoCapture cap;//视频获取结构，用来作为视频获取函数的一个参数
    Mat frame;//Mat类型，每一帧存放地址

    /********** 多线程和多线程处理 ********/
    QThread *thread1;
    QThread *thread2;
    QThread *thread3;
    QThread *thread4;

    void InitThread();
    void CloseThread();

    /********** init func **************/
    void InitUI();                      //初始化ui
    void InitConnect();                 //初始化信号槽
    void InitVar();                     //初始化变量

    /********** util func **************/
    void ChangeStatus(int flag);        //按钮隐藏状态切换
    void SavePicture();                 //保存图片到本地
    QImage FrameProcess(Mat frame);     //对每一帧进行处理
    QImage MatProcess(Mat resimg);      //具体处理图片
    void FaceEnqueue(Mat dstimg);       //图片加入人脸识别队列
};

#endif // OPENCAM_H
