/******************一些工具函数**********************/

#ifndef UTIL_H
#define UTIL_H

#include <QDebug>
#include <QDir>
#include <QString>
#include <QImage>
#include <QFile>
#include <QSettings>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <imgproc/imgproc.hpp>

using namespace cv;
/**************************
 *     数据，文件等处理     *
 * ***********************/

/**
 * @brief isDirExist
 * @param fullpath
 * @return
 */
bool IsDirExist(QString fullpath);

/**
 * @brief IsFileExist
 * @param filename
 * @return
 */
bool IsFileExist(QString filename);

/**
 * @brief InitIniText
 * @param filename
 */
void InitIniText(QString filename);

/**
 * @brief EditSetting
 * @param filename
 */
void EditSetting(QString filename, int width, int height, int flag, int mode, int face);

/***************************
 *        图片处理          *
 * *************************/

/**
 * @brief Mat2QImage
 * @param cvImg
 * @return
 */
QImage Mat2QImage(Mat cvImg);

/**
 * @brief ImgCut
 * @param img
 * @param img_w
 * @param img_h
 * @param w
 * @param h
 * @return
 */
QImage ImgCut(QImage img, int img_w, int img_h, int w, int h);

/**
 * @brief ImgScale
 * @param img
 * @param img_w
 * @param img_h
 * @param flag
 * @return
 */
QImage ImgScale(QImage img, int img_w, int img_h, int flag);

/**
 * @brief ImgZoom
 * @param img
 * @param ori_w
 * @param ori_h
 * @param flag
 * @return
 */
QImage ImgZoom(QImage img, int ori_w, int ori_h, int flag);

#endif // UTIL_H
