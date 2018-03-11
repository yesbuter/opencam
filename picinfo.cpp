#include "picinfo.h"

PicInfo::PicInfo()
{

}

const int PicInfo::ZOOMIN = 5;
const int PicInfo::ZOOMOUT = 0;
const int PicInfo::FRAME_C = 60;

bool PicInfo::init(QString filename)
{
    if(IsFileExist(filename))
    {
        //读
        QSettings settings(filename, QSettings::IniFormat);
        width = settings.value("PicInfo/width").toInt();
        height = settings.value("PicInfo/height").toInt();
        flag = settings.value("PicInfo/flag").toInt();
        mode = settings.value("PicInfo/mode").toInt();
        flag_face = settings.value("PicInfo/face").toInt();
        return true;
    }
    return false;
}

void PicInfo::setZoom(int z)
{
    zoom = z;
}

void PicInfo::setSize(int w, int h)
{
    width = w;
    height = h;
}

void PicInfo::setFlag(int f)
{
    flag = f;
}

void PicInfo::setFlagface(int f)
{
    flag_face = f;
}

void PicInfo::setMode(int m)
{
    mode = m;
}

int PicInfo::getWidth()
{
    return width;
}

int PicInfo::getHeight()
{
    return height;
}

int PicInfo::getMode()
{
    return mode;
}

int PicInfo::getFlag()
{
    return flag;
}

int PicInfo::getFlagface()
{
    return flag_face;
}

int PicInfo::getZoom()
{
    return zoom;
}
