#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent, char *url_) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    url = url_;

    view = new QWebEngineView(this);
    //view->load(QUrl("https://api.weibo.com/oauth2/authorize?redirect_uri=https%3A//api.weibo.com/oauth2/default.html&response_type=code&client_id=2375582409"));

    view->load(QUrl(url));

    setCentralWidget(view);

    resize(512, 340);

    progress = 0;

    // 关联信号和槽
    connect(view, &QWebEngineView::loadProgress, this, &MainWindow::setProgress);
    connect(view, &QWebEngineView::titleChanged, this, &MainWindow::adjustTitle);
    connect(view, &QWebEngineView::loadFinished, this, &MainWindow::finishLoading);

    locationEdit = new QLineEdit(this);
    locationEdit->setText(url);
    connect(locationEdit, &QLineEdit::returnPressed, this, &MainWindow::changeLocation);

    // 向工具栏添加动作和部件
    ui->mainToolBar->addAction(view->pageAction(QWebEnginePage::Back));
    ui->mainToolBar->addAction(view->pageAction(QWebEnginePage::Forward));
    ui->mainToolBar->addAction(view->pageAction(QWebEnginePage::Reload));
    ui->mainToolBar->addAction(view->pageAction(QWebEnginePage::Stop));
    ui->mainToolBar->addWidget(locationEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void setUrl(char* url_)
//{
//    this.url = url_;
//}

// 地址栏按下回车处理槽
void MainWindow::changeLocation()
{
    QUrl url = QUrl(locationEdit->text());
    view->load(url);
    view->setFocus();
}

void MainWindow::setProgress(int p)
{
    progress = p;
    adjustTitle();
}

// 调整标题槽
void MainWindow::adjustTitle()
{
    if ( progress <= 0 || progress >= 100) {
        setWindowTitle(view->title());
    } else {
        setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
    }
}

// 加载完成处理槽
void MainWindow::finishLoading(bool finished)
{
    if (finished) {
        progress = 100;
        setWindowTitle(view->title());
        qDebug() << view->title() << endl;
        QString ath_url = view->url().toString();
        locationEdit->setText(ath_url);
        if(ath_url.left(41) == "https://api.weibo.com/oauth2/default.html")
        {
            QString code = ath_url.right(32);
            qDebug() << ath_url << endl;
            qDebug() << code << endl;
            emit SendCode(code);
        }
    } else {
        setWindowTitle("web page loading error!");
    }
}

void MainWindow::upload_over()
{
    view->load(QUrl("http://www.weibo.com"));
}
