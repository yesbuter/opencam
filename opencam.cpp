#include "opencam.h"
#include "ui_opencam.h"
#include <QDebug>
Opencam::Opencam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Opencam)
{
    InitUI();                           //UI初始化

    InitIniText("./opencam.ini");       //初始化配置文件

    InitVar();                          //初始化变量

    picinfo->init("./opencam.ini");     //初始化状态

    InitConnect();                      //初始化信号槽

    OpenCamera();                       //打开摄像头
}

/*析构函数*/
Opencam::~Opencam()
{
    CloseCamera();
    frame.release();
    delete ui;
    if(this->timer != NULL)
    {
        delete this->timer;
        this->timer = NULL;
    }
    if(this->imag != NULL)
    {
        delete this->imag;
        this->imag = NULL;
    }
    if(this->picinfo != NULL)
    {
        delete this->picinfo;
        this->picinfo = NULL;
    }
    thread1 = NULL;
    thread2 = NULL;
    thread3 = NULL;
    thread4 = NULL;
}


/**************************************
 *             初始化函数              *
 * ************************************/

/**************** 初始化ui ******************/

void Opencam::InitUI()
{
    ui->setupUi(this);

    QGridLayout *mygridlayout = new QGridLayout();
    mygridlayout->addWidget(ui->widget_1, 0, 0, 1, 1);
    mygridlayout->addWidget(ui->widget_2, 0, 0, 1, 1);
    mygridlayout->setMargin(0);
    setLayout(mygridlayout);

    ui->widget_2->setStyleSheet("background-color:black;");

    ui->save->hide();
    ui->cancelsave->hide();
}

/**************** 初始化信号槽 ****************/

void Opencam::InitConnect()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(ReadFrame()));  // 时间到，读取当前摄像头
    connect(ui->takepic, SIGNAL(clicked()), this, SLOT(Take_Click()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(Save_Click()));
    connect(ui->cancelsave, SIGNAL(clicked()), this, SLOT(Cancel_Click()));
    connect(ui->zoomin, SIGNAL(clicked()), this, SLOT(ZoomIn_Click()));
    connect(ui->zoomout, SIGNAL(clicked()), this, SLOT(ZoomOut_Click()));
    connect(ui->settings, SIGNAL(clicked()), this, SLOT(Setting_Click()));
    connect(ui->showpic, SIGNAL(clicked()), this, SLOT(ShowPic_Click()));
}

/**************** 初始化变量 ******************/

void Opencam::InitVar()
{
    timer   = new QTimer(this);
    imag    = new QImage();
    picinfo = new PicInfo();
}

/**************** 重写关闭事件 ***************/
void Opencam::closeEvent(QCloseEvent *event)
{
    CloseCamera();
}


/***********************************************************
 *                        槽函数                            *
 * *********************************************************/

/********* 打开摄像头 ***********/
void Opencam::OpenCamera()
{

    cap = NULL;
    VideoCapture cap(1);
    if(!cap.isOpened())
    {
         printf("frame is empty\n");
    }
    //更新设置
    qDebug() << "11111111111111";
    SetContinue();
    qDebug() << "22222222222222";
    timer->start(picinfo->FRAME_C);              // 开始计时，不可缺少，控制频率，在这里为25帧
    //if(picinfo->getFlagface(：))
        //InitThread();
}


/********* 编辑readFrame()函数读取摄像头 ***********/

void Opencam::ReadFrame()
{

    cap>>frame;// 从摄像头中抓取并返回每一帧

    //处理每一帧
    QImage img_show = FrameProcess(frame);

    //label控件大小随窗口大小变化
    ui->label->resize(ui->widget_2->width(), ui->widget_2->height());
    ui->label->move(0, 0);

    //按窗口大小等比拉升
    img_show = ImgScale(img_show, ui->label->width(), ui->label->height(), 1);

    ui->label->setPixmap(QPixmap::fromImage(img_show));  // 将图片显示到label上
    ui->label->setAlignment(Qt::AlignCenter);
}


/********* 拍照按钮点击函数 ***********/

void Opencam::Take_Click()
{
    QImage imag_show = ImgScale(*this->imag, ui->label->width(), ui->label->height(), 1);
    ui->label->setPixmap(QPixmap::fromImage(imag_show));  // 将图片显示到label上
    ui->label->setAlignment(Qt::AlignCenter);
    //非连拍
    if(!picinfo->getFlag())
    {
        ChangeStatus(1);
        CloseCamera();
    }
    //连拍
    else
    {
        timer->stop();
        ui->label->clear();
        SavePicture();
        timer->start();
    }
}


/************** 关闭摄像头 **************/

void Opencam::CloseCamera()
{
    if(threadon)
    {
        CloseThread();
    }
    timer->stop();         // 停止读取数据
    cap.release();
}


/************** 点击保存按钮 ***************/

void Opencam::Save_Click()
{
    SavePicture();
    OpenCamera();
    ChangeStatus(0);
}


/**************** 点击取消按钮 ******************/

void Opencam::Cancel_Click()
{
    OpenCamera();
    ChangeStatus(0);
}


/***************** 放大按钮 **************/

void Opencam::ZoomIn_Click()
{
    int zoom = picinfo->getZoom();
    if(zoom < picinfo->ZOOMIN){
        zoom++;
        picinfo->setZoom(zoom);
        timer->stop();
        ui->label->clear();
        timer->start(picinfo->FRAME_C);
    }
}


/**************** 缩小按钮 ***************/

void Opencam::ZoomOut_Click()
{
    int zoom = picinfo->getZoom();
    if(zoom > picinfo->ZOOMOUT)
    {
        zoom--;
        picinfo->setZoom(zoom);
        timer->stop();
        ui->label->clear();
        timer->start(picinfo->FRAME_C);
    }
}

void Opencam::ShowPic_Click()
{
    EditWindow *editwindow = new EditWindow();
    editwindow->setAttribute(Qt::WA_DeleteOnClose);
    editwindow->show();
}

/**************** 设置按钮 ***************/

void Opencam::Setting_Click()
{
    //todo
    QDialog *dialog = new SettingDialog(this);
    dialog->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint);    //去掉标题栏
    dialog->setAttribute(Qt::WA_DeleteOnClose);     //关闭时销毁对象
    //绑定信号槽
    connect(this,SIGNAL(PicinfoSend(PicInfo *)), dialog,SLOT(ReceivePicinfo(PicInfo*)));
    connect(dialog, SIGNAL(IsClose()), this, SLOT(SetContinue()));
    //发送信号传递Picinfo信息
    emit PicinfoSend(picinfo);
    dialog->show();
}


/**************************************
 *             工具函数                *
 * ************************************/

/************** 处理每一帧 *************/

QImage Opencam::FrameProcess(Mat frame)
{
    //count = 2;
    QImage resimg;
    QImage showimg;
    Mat dstmat = Mat(frame.size(), CV_8UC3);
    Mat showmat = Mat(frame.size(), CV_8UC3);

    //todo:加效果，黄昏，强光，白平衡
    //dstImage = ComicStripColor(frame);

    dstmat = frame.clone();
    showmat = frame.clone();

    //std::vector<Rect> tmpfaces = faces;
    if(picinfo->getFlagface())
    {
        FaceEnqueue(frame.clone());
        showmat = DrawRec(showmat, count);
    }

    resimg = MatProcess(dstmat);
    showimg = MatProcess(showmat);

    dstmat.release();
    showmat.release();

    *this->imag = resimg;

    return showimg;
}

QImage Opencam::MatProcess(Mat dstimg)
{
    QImage resimg;
    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式
    resimg = Mat2QImage(dstimg);

    //按比例裁剪
    resimg = ImgCut(resimg, resimg.width(), resimg.height(), picinfo->getWidth(), picinfo->getHeight());

    //放缩
    if(picinfo->getZoom() > picinfo->ZOOMOUT || picinfo->getZoom() < picinfo->ZOOMOUT)
    {
        resimg = ImgZoom(resimg, resimg.width(), resimg.height(), picinfo->getZoom());
    }

    //旋转
    resimg = resimg.mirrored(true, false);

    return resimg;
}

void Opencam::FaceEnqueue(Mat dstmat)
{
    Mat* buffer = NULL;
    if(count == 2)
    {
        //跳帧入队进行人脸识别
        Mat *tmpimg = new Mat(frame.size(), CV_8UC3);
        *tmpimg = dstmat;
        if(mat_q->getQueueSize() >= 3)
            buffer = (Mat*)mat_q->dequeue();
        if(NULL != buffer){
            buffer->release();
            free(buffer);
        }
        mat_q->enqueue(tmpimg);
        count = 0;
    }
    else
        count++;
}

/************** 界面按钮隐藏和显示 **************/
/* flag = 0 : 拍摄界面 */
/* flag = 1 : 保存界面 */

void Opencam::ChangeStatus(int flag)
{
    //保存界面
    if(flag)
    {
        ui->save->show();
        ui->cancelsave->show();
        ui->takepic->hide();
        ui->settings->hide();
        ui->showpic->hide();
        ui->zoomin->hide();
        ui->zoomout->hide();
    }
    //拍摄界面
    else
    {
        ui->cancelsave->hide();
        ui->save->hide();
        ui->takepic->show();
        ui->settings->show();
        ui->showpic->show();
        ui->zoomin->show();
        ui->zoomout->show();
    }
}


/***************** 图片保存 ****************/

void Opencam::SavePicture()
{
    if(this->imag != NULL)
    {
        QImage img_save = *this->imag;
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date =current_date_time.toString("yyyy-MM-dd-hh-mm-ss-zzz");
        current_date.append(".jpg");
        QString filepath = "./opencampic/";
        if(IsDirExist(filepath))
        {
            filepath.append(current_date);
            qDebug() << "filepath:" << filepath;
            bool tmpflag = img_save.save(filepath);
            qDebug() << "saveflag:" << tmpflag;
        }
        else
            qDebug() << "savepath wrong";
    }
}

/***************** 设置更新后 *****************/

void Opencam::SetContinue()
{
    if(picinfo->getFlag())
    {
        ui->takepic->setAutoRepeat(true);
        ui->takepic->setAutoRepeatDelay(1000);
        ui->takepic->setAutoRepeatInterval(2000);
    }
    else
    {
        ui->takepic->setAutoDefault(false);
    }
    qDebug() << "333333333333333";
    if(picinfo->getFlagface())
    {
        if(!threadon)
        {
            InitThread();
        }
    }
    else
    {
        if(threadon)
        {
            CloseThread();
        }
    }
}

/********************* 线程管理 ******************/

void Opencam::InitThread()
{
    thread1 = new FaceProcess();
    thread2 = new FaceProcess();
    thread3 = new FaceProcess();
    thread4 = new FaceProcess();
    threadon = 1;
}

void Opencam::CloseThread()
{
    delete thread1;
    delete thread2;
    delete thread3;
    delete thread4;
    threadon = 0;
}
