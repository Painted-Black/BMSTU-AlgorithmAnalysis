#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <thread>

#include <QMutex>

class MyMatrix
{
public:
    MyMatrix(int rows, int cols, bool randomize=false, int defaultValue=0);
    MyMatrix(const MyMatrix& m);
    MyMatrix(std::vector<std::vector<int>> &vec);
    MyMatrix(std::initializer_list<std::initializer_list<int>> list);
    ~MyMatrix();

    void print() const;
    int at(int row, int col) const;
    void set(int row, int col, int val);
    MyMatrix multiplyVinograd(const MyMatrix& m);
    MyMatrix multiplyVinograd_multithread(const MyMatrix& m, int threadsNumber);
    bool isEqual(const MyMatrix& m);

private:
    void threadMultiply(const MyMatrix& m1, const MyMatrix &m2, MyMatrix &res, int *mulH, int *mulV, int from_i, int to_i);
    int mColumns;
    int mRows;
    int *mValues;
    int mMinRand = -50;
    int mRandRange = 100;
};

#endif // MYMATRIX_H
