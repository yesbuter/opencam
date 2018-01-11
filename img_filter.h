#ifndef IMG_FILTER_H
#define IMG_FILTER_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

/**
 * auth:司月
 * time:2018.01.10
 * commen:滤镜
 * param: 待处理图片
 * print: 处理后图片
 * */

/* 复古 */
Mat VintageColor(Mat srcImage);

/* 连环画 */
Mat ComicStripColor(Mat srcImage);

/* 熔铸 */
Mat Casting(Mat srcImage);

/* 浮雕 */
Mat Emboss(Mat srcImage);

/* 哈哈镜——扩张（滤镜） */
Mat Enlarge(Mat srcImage);


#endif // IMG_FILTER_H
