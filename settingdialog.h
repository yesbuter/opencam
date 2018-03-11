#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QDebug>
#include <picinfo.h>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

signals:
    void IsClose();

private slots:
    void Confirm_Clicked();                 //确认按钮
    void Cancel_Clicked();                  //取消按钮
    void ReceivePicinfo(PicInfo *picinfo);  //接收picinfo

private:
    Ui::SettingDialog *ui;
    PicInfo *tmp_picinfo;

    void InitUI();

    void Pic2Dialog();
    void Dialog2Pic();
    void Dialog2Set();
};

#endif // SETTINGDIALOG_H
