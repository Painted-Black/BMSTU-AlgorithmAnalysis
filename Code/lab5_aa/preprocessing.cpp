#include "preprocessing.h"

PreProcessing::PreProcessing(int count, QTime *timer, Processing *p, QMutex *mutex2)
{
    this->_count = count;
    this->_timer = timer;
    this->_proc = p;
    this->_mutex2 = mutex2;
}

void PreProcessing::addToQueue(MyObject obj)
{
    _queue.push(obj);
}

void PreProcessing::process()
{
    while (preprocessed != _count)
    {
        if (_queue.size() != 0)
        {
            // cout << "PreProcessing" << _timer->elapsed() << endl;
            MyObject obj = _queue.front();
            QThread thread;
            obj.setTime(_timer->elapsed());
            thread.msleep(_PROCESSING_TIME);
            obj.setTime(_timer->elapsed());
            _queue.pop();
            _mutex2->lock();
            _proc->addToQueue(obj);
            _mutex2->unlock();
            preprocessed++;
        }
    }
}
