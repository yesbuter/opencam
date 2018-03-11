#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <mainwindow.h>
#include <util.h>
#include <Python.h>
#include <QDebug>
#include <iostream>
#include <list>
#include <algorithm>

namespace Ui {
class EditWindow;
}

class EditWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditWindow(QWidget *parent = 0);
    ~EditWindow();

signals:
    void upload_over();

private slots:
    void on_weiboButton_clicked();
    void on_code_get(QString);

private:
    Ui::EditWindow *ui;

/*---------------  ui -------------*/
    QGridLayout *mygridlayout;

    QScrollArea *scroll_tab_1;
    QScrollArea *scroll_tab_2;
    QVBoxLayout *vbox_tab_1;
    QVBoxLayout *vbox_tab_2;

    void InitUI();

/*************** python-weibo **************/

    PyObject * pModule = NULL;
    PyObject * pFunc   = NULL;
    PyObject * url_=NULL;
    PyObject * pParam = NULL;

    void Py_Init();
    void Py_Final();

    char* getUrl();

/***************** 相册 ********************/
    std::list<QString> picname_list;
    void GetFilename(QString path);
    Mat editmat;
};

#endif // EDITWINDOW_H
