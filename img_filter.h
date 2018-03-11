#ifndef IMG_FILTER_H
#define IMG_FILTER_H

#include <QMutex>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <dataqueue.h>

using namespace cv;
using namespace std;

/**
 * auth:司月
 * time:2018.01.10
 * commen:滤镜
 * param: 待处理图片
 * print: 处理后图片
 * */

/************************ 滤镜 *************************/

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

/************************* 美颜 **************************/

/* 美白 */
//todo

/* 磨皮 */
//todo

/************************* 模式 **************************/

/* 人脸识别 */
extern std::vector<Rect> faces;
extern std::vector<Rect> tmpfaces;
extern QMutex mutex;

void FaceDetection(Mat srcImage);

Mat DrawRec(Mat srcImage, int count);

/* 黄昏 */
//todo

/* 强光 */
//todo

/* 白平衡 */
//todo

/************************* 贴图 **************************/

/* 加帽子 */
void MapToHead(Mat &hat, Mat &srcImage, int x, int y);

Mat detectFace(Mat srcImage);

#endif // IMG_FILTER_H
