#include "util.h"


/******************************* 文件，数据 ********************************/


bool IsDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())
    {
      return true;
    }
    else
    {
       bool ok = dir.mkpath(fullPath);//创建多级目录
       return ok;
    }
}

bool IsFileExist(QString filename)
{
    QFileInfo fileInfo(filename);
    if(fileInfo.isFile())
    {
        return true;
    }
    else
        return false;
}

void InitIniText(QString filename)
{
    if(IsFileExist(filename))
        return;
    else
    {
        //宽，高，是否连拍，模式，是否人脸识别
        EditSetting(filename, 1, 1, 0, 0, 1);
    }
}

void EditSetting(QString filename, int width, int height, int flag, int mode, int face)
{
    QFile file(filename);
    QSettings settings(filename, QSettings::IniFormat);
    settings.setValue("PicInfo/width", width);
    settings.setValue("PicInfo/height", height);
    settings.setValue("PicInfo/flag", flag);
    settings.setValue("PicInfo/mode", mode);
    settings.setValue("PicInfo/face", face);
}


/****************************** 图片 ***********************************/

QImage Mat2QImage(Mat cvImg)
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

QImage ImgCut(QImage img, int img_w, int img_h, int w, int h)
{
    QImage result = img;
    //过于宽
    if(img_w * h / w > img_h)
        result = img.copy((img_w - img_h / h * w) / 2, 0, img_h / h * w,img_h);
    //过于高
    else if(img_w * h / w < img_h)
        result = img.copy(0, (img_h - img_w / w * h) / 2, img_w, img_w / w * h);
    //QImage result = img.copy(img, img_h, img_w, 0);
    return result;
}

QImage ImgScale(QImage img, int img_w, int img_h, int flag)
{
    QImage result;
    if(flag)
        result = img.scaled(img_w, img_h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    else
        result = img.scaled(img_w, img_h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    return result;
}

QImage ImgZoom(QImage img, int ori_w, int ori_h, int flag)
{
    //flag是级别
    int n_w, n_h;
    n_w = ori_w;
    n_h = ori_h;

    while(flag--)
    {
        n_w = n_w * 4 / 5;
        n_h = n_h * 4 / 5;
    }
    img = img.copy((ori_w - n_w) / 2, (ori_h - n_h) / 2, n_w, n_h);
    img = ImgScale(img, ori_w, ori_h, 1);


    return img;
}
