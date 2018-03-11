#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    InitUI();
    connect(ui->confirm, SIGNAL(clicked()), this, SLOT(Confirm_Clicked()));
}

/************************** 加载控件 *********************/

void SettingDialog::InitUI()
{
    ui->setupUi(this);

    ui->scale_item->addItem(tr("1 : 1"));
    ui->scale_item->addItem(tr("4 : 3"));
    ui->scale_item->addItem(tr("16 : 9"));

    ui->mode_item->addItem(tr("None"));
    ui->mode_item->addItem(tr("Dusk Modal"));
    ui->mode_item->addItem(tr("Hard Light"));
    ui->mode_item->addItem(tr("White Balance"));
}


/************************** 槽函数 ***********************/

SettingDialog::~SettingDialog()
{
    delete ui;
    tmp_picinfo = NULL;
}

void SettingDialog::ReceivePicinfo(PicInfo *picinfo)
{
    this->tmp_picinfo = picinfo;
    //qDebug() << picinfo->getWidth();

    //初始化控件状态
    Pic2Dialog();
}

void SettingDialog::Confirm_Clicked()
{
    //跟进控件状态
    Dialog2Pic();
    //更新配置文件
    Dialog2Set();
    //更新连拍状态
    emit IsClose();
    close();
}

void SettingDialog::Cancel_Clicked()
{
    emit IsClose();
    close();
}


/************************** 功能函数 **********************/

void SettingDialog::Pic2Dialog()
{
    //比例
    if(tmp_picinfo->getWidth() == 1)
        ui->scale_item->setCurrentIndex(0);
    else if(tmp_picinfo->getWidth() == 4)
        ui->scale_item->setCurrentIndex(1);
    else if(tmp_picinfo->getWidth() == 16)
        ui->scale_item->setCurrentIndex(2);

    //人脸识别
    if(tmp_picinfo->getFlagface())
        ui->face_recog->setCheckState(Qt::Checked);
    else
        ui->face_recog->setCheckState(Qt::Unchecked);

    //连拍
    if(tmp_picinfo->getFlag())
        ui->continue_cap->setCheckState(Qt::Checked);
    else
        ui->continue_cap->setCheckState(Qt::Unchecked);

    //模式
    ui->mode_item->setCurrentIndex(tmp_picinfo->getMode());
}

void SettingDialog::Dialog2Pic()
{
    //比例
    if(ui->scale_item->currentIndex() == 0)
        tmp_picinfo->setSize(1, 1);
    else if(ui->scale_item->currentIndex() == 1)
        tmp_picinfo->setSize(4, 3);
    else if(ui->scale_item->currentIndex() == 2)
        tmp_picinfo->setSize(16, 9);

    //模式
    tmp_picinfo->setMode(ui->mode_item->currentIndex());

    //连拍
    if(Qt::Checked == ui->continue_cap->checkState())
        tmp_picinfo->setFlag(1);
    else
        tmp_picinfo->setFlag(0);

    //人脸识别
    if(Qt::Checked == ui->face_recog->checkState())
        tmp_picinfo->setFlagface(1);
    else
        tmp_picinfo->setFlagface(0);
    qDebug() << ui->face_recog->checkState();
    qDebug() << "tmppicinfo" << tmp_picinfo->getFlagface();
}

void SettingDialog::Dialog2Set()
{
    EditSetting("./opencam.ini", tmp_picinfo->getWidth(), tmp_picinfo->getHeight(),tmp_picinfo->getFlag(), tmp_picinfo->getMode(), tmp_picinfo->getFlagface());
}
