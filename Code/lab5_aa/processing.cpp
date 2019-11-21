#include "processing.h"

Processing::Processing(int count, QTime *timer, PostProcessing *p, QMutex *mutex2, QMutex *mutex3)
{
    this->_count = count;
    this->_timer = timer;
    this->_proc = p;
    this->_mutex2 = mutex2;
    this->_mutex3 = mutex3;
}

void Processing::addToQueue(MyObject obj)
{
    _queue.push(obj);
}

void Processing::process()
{
    while (processed != _count)
    {
        if (_queue.size() != 0)
        {
            // cout << "Processing" << _timer->elapsed() << endl;
            MyObject obj = _queue.front();
            QThread thread;
            obj.setTime(_timer->elapsed());
            thread.msleep(_PROCESSING_TIME);
            obj.setTime(_timer->elapsed());

            _mutex2->lock();
            _queue.pop();
            _mutex2->unlock();

            _mutex3->lock();
            _proc->addToQueue(obj);
            _mutex3->unlock();

            processed++;
        }
    }
}
