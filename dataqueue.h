#ifndef DATAQUEUE_H
#define DATAQUEUE_H

#include <QQueue>
#include <QMutexLocker>

class DataQueue
{
    QMutex m_mutex;QQueue<void*> m_datas;
public:
    DataQueue();
    void enqueue(void*);void* dequeue();
    int getQueueSize();
};

extern DataQueue *mat_q;
extern DataQueue *rec_q;

#endif // DATAQUEUE_H
