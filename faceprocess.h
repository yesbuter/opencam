#ifndef FACEPROCESS_H
#define FACEPROCESS_H

#include <QThread>
#include <QDebug>
#include <QMutex>
#include <dataqueue.h>
#include <img_filter.h>

class FaceProcess : public QThread
{
    Q_OBJECT
    void run() override {
        setRunningFlag(true);

        Mat *buffer=NULL;
        while(getRunningFlag()){

            buffer= (Mat*)mat_q->dequeue();
            if(NULL==buffer){msleep(5);continue;}

            FaceDetection(*buffer);
            buffer->release();
            delete buffer;
        }
    }

public:
    FaceProcess();
    ~FaceProcess();
    bool getRunningFlag();
    void setRunningFlag(bool bRun);

private:
    bool m_brun;
    QMutex m_mutex;

};

#endif // FACEPROCESS_H
