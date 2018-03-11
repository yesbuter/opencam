#include "editwindow.h"
#include "ui_editwindow.h"

EditWindow::EditWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);

    InitUI();
    GetFilename("./opencampic");
}

void EditWindow::InitUI()
{
    mygridlayout = new QGridLayout();
    mygridlayout->addWidget(ui->tabWidget, 0, 0, 4, 2);
    mygridlayout->addWidget(ui->savebutton, 4, 0, 1, 2);
    mygridlayout->addWidget(ui->resetbutton, 5, 0, 1, 2);
    mygridlayout->addWidget(ui->widget, 0, 2, 4, 6);
    mygridlayout->addWidget(ui->left, 0, 2, 4, 3);
    mygridlayout->addWidget(ui->right, 0, 5, 4, 3);
    mygridlayout->addWidget(ui->meibailabel, 4, 2, 2, 1);
    mygridlayout->addWidget(ui->horizontalSlider, 4, 3, 2, 4);
    mygridlayout->addWidget(ui->weiboButton, 4, 7, 2, 1);

    mygridlayout->setColumnMinimumWidth(0, 70);
    mygridlayout->setColumnMinimumWidth(1, 70);

    scroll_tab_2 = new QScrollArea();
    QWidget *widget = new QWidget();
    widget->setLayout(ui->gridLayout_3);
    scroll_tab_2->setWidget(widget);
    vbox_tab_2 = new QVBoxLayout(this);
    vbox_tab_2->addWidget(scroll_tab_2);
    ui->tab_2->setLayout(vbox_tab_2);

    ui->left->setFlat(false);
    this->setLayout(mygridlayout);
}

EditWindow::~EditWindow()
{
    delete ui;
    delete mygridlayout;
    mygridlayout = NULL;
}

void EditWindow::on_weiboButton_clicked()
{
    MainWindow *mywindow = new MainWindow(0, getUrl());
    mywindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(mywindow, SIGNAL(SendCode(QString)), this, SLOT(on_code_get(QString)));
    connect(this, SIGNAL(upload_over()), mywindow, SLOT(upload_over()));
    mywindow->show();
    //on_code_get("0323811242d48da01b80ad1b0132f7cc");
}

void EditWindow::on_code_get(QString code)
{
    QByteArray ba = code.toLatin1();
    char* code_c = ba.data();
    //std::cout << "1111" << endl;
    Py_Init();
    pModule = PyImport_ImportModule("upload_weibo");
    pFunc = PyObject_GetAttrString(pModule, "upload_pic");
    pParam = Py_BuildValue("(s)", code_c);
    PyEval_CallObject(pFunc, pParam);
    Py_Final();
    emit upload_over();
}

char* EditWindow::getUrl()
{
    Py_Init();
    pModule = PyImport_ImportModule("py_geturl");
    pFunc   = PyObject_GetAttrString(pModule, "get_access_token");
    url_=PyEval_CallObject(pFunc,NULL);
    char* url;
    PyArg_Parse(url_,"s",&url);
    Py_Final();
    pModule = NULL;
    pFunc = NULL;
    url_ = NULL;
    return url;
}

void EditWindow::Py_Init()
{
    if(!Py_IsInitialized())
        Py_Initialize();
}
void EditWindow::Py_Final()
{
    if(pModule)
        Py_DECREF(pModule);
    if(pFunc)
        Py_DECREF(pFunc);
    if(url_)
        Py_DECREF(url_);
    if(pParam)
        Py_DECREF(pParam);
    if(Py_IsInitialized())
    {
        Py_Finalize();
    }
}

void EditWindow::GetFilename(QString path)
{
    qDebug() << "begin";
    //判断路径是否存在
    QDir dir(path);
    if(!dir.exists())
    {
        qDebug() << "path not found";
        return;
    }
    //查看路径中后缀为.jpg格式的文件
    QStringList filters;
    filters<<QString("*.jpg");
    dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
    dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式

    //统计cfg格式的文件个数
    int dir_count = dir.count();
    if(dir_count <= 0)
    {
        qDebug() << "num 0";
        return;
    }


    //存储文件名到成员变量
    for(int i=0; i<dir_count; i++)
    {
        QString file_name = dir[i];  //文件名称
        //ts<<file_name<<"\r\n"<<"\r\n";
        picname_list.push_back(file_name);
    }
    picname_list.sort();
    for(std::list<QString>::iterator it = picname_list.begin(); it != picname_list.end(); it++)
    {
        qDebug() << *it;
    }
    return;
}
