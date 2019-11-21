#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


class MyObject
{
public:
    MyObject(int id);
    void setTime(int time);
    void printTimes();
    void timesToFile(ofstream &fout);
private:
    int _id;
    vector<int> _times;
};

#endif // MYOBJECT_H
