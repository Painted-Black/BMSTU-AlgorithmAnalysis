#ifndef TESTMYMATRIX_H
#define TESTMYMATRIX_H

#include <QObject>
#include <QtTest/QtTest>

#include "mymatrix.h"

class TestMyMatrix : public QObject
{
    Q_OBJECT
public:
    explicit TestMyMatrix(QObject *parent = nullptr);
    typedef MyMatrix (MyMatrix::*func)(const MyMatrix& m);
private:
    const int MIN_MATRIX_SIZE = 0;
    const int MAX_MATRIX_SIZE = 200;
    const int TESTS_PER_SIZE = 1;
    const int SIZE_STEP = 10;
    const int LOGIC_KERNELS = 4;

private slots:
    void TestMultiplies();
    void TestPairsSquare();
    void TestPairsNotSquare();
};

#endif // TESTMYMATRIX_H
