#include "faceprocess.h"

bool FaceProcess::getRunningFlag(){
    QMutexLocker locker(&m_mutex);
    return m_brun;
}
void FaceProcess::setRunningFlag(bool bRun){
    QMutexLocker locker(&m_mutex);
    m_brun = bRun;
}

FaceProcess::FaceProcess(){start();}
FaceProcess::~FaceProcess(){
    setRunningFlag(false);
    wait();
}
