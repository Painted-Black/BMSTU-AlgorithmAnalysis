#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <ctime>
#include <vector>

class MyMatrix
{
public:
    MyMatrix(int rows, int cols, bool randomize=false, int defaultValue=0);
    MyMatrix(const MyMatrix& m);
    MyMatrix(std::vector<std::vector<int>> &vec);
    MyMatrix(std::initializer_list<std::initializer_list<int>> list);
    ~MyMatrix();

    void print();
    int at(int row, int col) const;
    void set(int row, int col, int val);
    MyMatrix multiply(const MyMatrix& m);
    MyMatrix multiplyVinograd(const MyMatrix& m);
    MyMatrix multiplyVinogradOptimized(const MyMatrix& m);
    bool isEqual(const MyMatrix& m);
    bool isEqual(const MyMatrix& m1, const MyMatrix& m2);

private:
    int mColumns;
    int mRows;
    int *mValues;
    int mMinRand = -50;
    int mRandRange = 100;
};

#endif // MYMATRIX_H
