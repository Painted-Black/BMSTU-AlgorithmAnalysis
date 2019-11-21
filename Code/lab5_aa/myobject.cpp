#include "myobject.h"

MyObject::MyObject(int id)
{
    this->_id = id;
}

void MyObject::setTime(int time)
{
    this->_times.push_back(time);
}

void MyObject::printTimes()
{
    cout << "Object" << _id << "\t\t";
    for (unsigned int i = 0; i < _times.size(); ++i)
        cout << _times.at(i) << "  ";
    cout << endl;
}

void MyObject::timesToFile(ofstream &fout)
{
    fout << "Object" << _id << "\t\t";
    for (unsigned int i = 0; i < _times.size(); ++i)
    {
        fout << _times.at(i) << "  ";
    }
    fout << endl;
}
