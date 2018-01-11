#include "opencam.h"
#include "ui_opencam.h"

opencam::opencam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::opencam)
{
    ui->setupUi(this);
    timer   = new QTimer(this);
    imag    = new QImage();         // 初始化


    /*信号和槽*/
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头
    connect(ui->open, SIGNAL(clicked()), this, SLOT(openCamera()));
    connect(ui->pic, SIGNAL(clicked()), this, SLOT(takingPictures()));
    connect(ui->closeCam, SIGNAL(clicked()), this, SLOT(closeCamera()));
}

/******************************
********* 编辑opencamera ***********
*******************************/
void opencam::openCamera()
{

    cap = NULL;
    VideoCapture cap(1);
    if(!cap.isOpened())
    {
         printf("frame is empty\n");
    }

    timer->start(40);              // 开始计时，不可缺少，控制频率，在这里为25帧
}

QImage opencam::Mat2QImage(Mat cvImg)
{
    QImage qImg;
    if(cvImg.channels()==3)                             //3 channels color image
    {
        cvtColor(cvImg,cvImg,CV_BGR2RGB);
        qImg =QImage((const unsigned char*)(cvImg.data),
                     cvImg.cols, cvImg.rows,
                     cvImg.cols*cvImg.channels(),
                     QImage::Format_RGB888);
    }
    else if(cvImg.channels()==1)                    //grayscale image
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                     cvImg.cols,cvImg.rows,
                     cvImg.cols*cvImg.channels(),
                     QImage::Format_Indexed8);
    }
    else
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                     cvImg.cols,cvImg.rows,
                     cvImg.cols*cvImg.channels(),
                     QImage::Format_RGB888);
    }
    return qImg;
}
/*********************************
********* 编辑readFrame()函数读取摄像头 ***********
**********************************/
void opencam::readFarme()
{

    cap>>frame;// 从摄像头中抓取并返回每一帧
    Mat dstImage(frame.size(), CV_8UC3);
    dstImage = Enlarge(frame);
    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式
    QImage imag = Mat2QImage(dstImage);
    ui->label->setPixmap(QPixmap::fromImage(imag));  // 将图片显示到label上
}

///*************************
//********* 拍照设置 ***********
//**************************/
void opencam::takingPictures()
{

    cap>>frame;// 从摄像头抓取并返回每一帧
    //imwrite("frame.jpg",frame);
    Mat dstImage(frame.size(), CV_8UC3);
    dstImage = VintageColor(frame);
    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式
    QImage imag = Mat2QImage(dstImage);

    ui->label_2->setPixmap(QPixmap::fromImage(imag));  // 将图片显示到label上
}

/*******************************
***关闭摄像头***
********************************/
void opencam::closeCamera()
{
    timer->stop();         // 停止读取数据
    cap.release();
}

opencam::~opencam()
{
    delete ui;
}
