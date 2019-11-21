#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <iostream>
#include <queue>
#include <QThread>
#include <QTime>
#include <QMutex>

#include "myobject.h"
#include "processing.h"

using namespace std;

class PreProcessing
{
public:
    PreProcessing(int count, QTime *timer, Processing *p, QMutex *mutex2);
    void addToQueue(MyObject obj);
    void process();
private:
    queue<MyObject> _queue;
    QTime *_timer;
    Processing *_proc;
    QMutex *_mutex2;
    int _count;
    int preprocessed = 0;
    const unsigned int _PROCESSING_TIME = 50;
};

#endif // PREPROCESSING_H
