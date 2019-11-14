#ifndef TESTMYARRAY_H
#define TESTMYARRAY_H

#include <QObject>
#include <QtTest/QtTest>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <ctime>

#include "myarray.h"

class TestMyArray : public QObject
{
    Q_OBJECT
public:
    TestMyArray();
private:
    std::vector<int> randomVector(int size, int minValue=-50, int range=100);
private slots:
    void testSameElements();
    void testDifferentPositiveElements();
    void testDifferentNegativeElements();
    void testDifferentElements();

    void compareSortingsResults();
};

#endif // TESTMYARRAY_H
