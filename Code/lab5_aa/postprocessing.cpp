#include "postprocessing.h"

PostProcessing::PostProcessing(int count, QTime *timer, vector<MyObject> *dump, QMutex *mutex3)
{
    this->_count = count;
    this->_timer = timer;
    this->_dump = dump;
    this->_mutex3 = mutex3;
}

void PostProcessing::addToQueue(MyObject obj)
{
    _queue.push(obj);
}

void PostProcessing::process()
{
    while (postprocessed != _count)
    {
        if (_queue.size() != 0)
        {
            // cout << "PostProcessing" << _timer->elapsed() << endl;
            MyObject obj = _queue.front();
            QThread thread;
            obj.setTime(_timer->elapsed());
            thread.msleep(_PROCESSING_TIME);
            obj.setTime(_timer->elapsed());

            _mutex3->lock();
            _queue.pop();
            _mutex3->unlock();

            _dump->push_back(obj);
            postprocessed++;
        }
    }
}
