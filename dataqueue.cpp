#include "dataqueue.h"

DataQueue::DataQueue()
{

}
void DataQueue::enqueue(void *data){
    QMutexLocker locker(&m_mutex);
    m_datas.enqueue(data);
}
void* DataQueue::dequeue(){
    QMutexLocker locker(&m_mutex);
    return m_datas.empty()?NULL:m_datas.dequeue();
}

int DataQueue::getQueueSize()
{
    return m_datas.size();
}

DataQueue *mat_q = new DataQueue();
DataQueue *rec_q = new DataQueue();
