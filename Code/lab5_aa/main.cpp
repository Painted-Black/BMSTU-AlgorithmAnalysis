#include <QCoreApplication>
#include <QTime>
#include <QMutex>

#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <fstream>

#include "myobject.h"
#include "preprocessing.h"
#include "processing.h"
#include "postprocessing.h"

using namespace std;

const int COUNT = 10;

const string LOG_FILE = "/home/syzygy/lab5_aa/times";

void consistent();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    consistent();

    QTime timer;
    timer.restart();

    int start_time = timer.elapsed();

    vector<MyObject> dump;

    QMutex *mutex2 = new QMutex;
    QMutex *mutex3 = new QMutex;

    PostProcessing *postproc = new PostProcessing(COUNT, &timer, &dump, mutex2);
    Processing *proc = new Processing(COUNT, &timer, postproc, mutex2, mutex3);
    PreProcessing *preproc = new PreProcessing(COUNT, &timer, proc, mutex3);

    for (int i = 0; i < COUNT; ++i)
    {
        MyObject obj(i);
        preproc->addToQueue(obj);
    }

    vector<thread> threads;
    threads.push_back(thread(&PreProcessing::process, preproc));
    threads.push_back(thread(&Processing::process, proc));
    threads.push_back(thread(&PostProcessing::process, postproc));

    for (unsigned int i = 0; i <  threads.size(); ++i)
    {
        if (threads.at(i).joinable())
            threads.at(i).join();
    }

    int total_time = timer.elapsed() - start_time;

    ofstream fout(LOG_FILE);
    if (fout.is_open())
    {
        for (unsigned int i = 0; i < dump.size(); ++i)
            dump.at(i).timesToFile(fout);
        fout << "Total time: " << total_time << endl;
        cout << "Результаты записаны в файл: " << LOG_FILE << endl;
    }
    else
        cout << "Невозможно открыть файл " << LOG_FILE << endl;
    fout.close();


    delete mutex2;
    delete mutex3;
    delete preproc;
    delete proc;
    delete postproc;

    return 0;
}

void consistent()
{
    QTime timer;
    timer.restart();

    int start_time = timer.elapsed();

    vector<MyObject> dump;

    QMutex *mutex2 = new QMutex;
    QMutex *mutex3 = new QMutex;

    PostProcessing *postproc = new PostProcessing(COUNT, &timer, &dump, mutex2);
    Processing *proc = new Processing(COUNT, &timer, postproc, mutex2, mutex3);
    PreProcessing *preproc = new PreProcessing(COUNT, &timer, proc, mutex3);

    for (int i = 0; i < COUNT; ++i)
    {
        MyObject obj(i);
        preproc->addToQueue(obj);
    }

    preproc->process();
    proc->process();
    postproc->process();

    int total_time = timer.elapsed() - start_time;

    ofstream fout(LOG_FILE);
    if (fout.is_open())
    {
        for (unsigned int i = 0; i < dump.size(); ++i)
            dump.at(i).timesToFile(fout);
        fout << "Total time: " << total_time << endl;
        cout << "Результаты записаны в файл: " << LOG_FILE << endl;
    }
    else
        cout << "Невозможно открыть файл " << LOG_FILE << endl;
    fout.close();


    delete mutex2;
    delete mutex3;
    delete preproc;
    delete proc;
    delete postproc;
}
