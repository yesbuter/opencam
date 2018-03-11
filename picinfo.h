#ifndef PICINFO_H
#define PICINFO_H

#include <QString>
#include <QSettings>
#include <util.h>

class PicInfo
{
public:
    PicInfo();

    void setSize(int w, int h);
    void setFlag(int f);
    void setFlagface(int f);
    void setMode(int m);
    void setZoom(int z);

    int getFlagface();
    int getWidth();
    int getHeight();
    int getFlag();
    int getMode();
    int getZoom();

    //根据ini文件初始化
    bool init(QString filename);

    //放缩上限
    const static int ZOOMIN;
    //放缩下限
    const static int ZOOMOUT;

    //帧数
    const static int FRAME_C;

private:
    int width = 1;
    int height = 1;
    //放缩级别 0-5, 不根据ini文件初始化
    int zoom = 0;
    //是否长按相机连拍
    int flag = 1;
    //是否开启人脸识别
    int flag_face = 1;
    //0：无，1：黄昏，2：强光，3：白平衡
    int mode = 0;
};

#endif // PICINFO_H
