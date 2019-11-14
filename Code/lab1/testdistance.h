#ifndef TESTDISTANCE_H
#define TESTDISTANCE_H

#include <stdlib.h>
#include <QtTest/QtTest>
#include <ctime>

#include "levenshteindistance.h"

class TestDistance : public QObject
{
    Q_OBJECT
private slots:
    void testEmptyString();
    void testSameStrings();
    void testDifferentStrings();
    void test_levenshteinDistance_m();
    void test_levenshteinDistance_r();
    void test_damerauLevenshteinDistance_m();
    void test_damerauLevenshteinDistance_r();
    void testPairsEmpty();
    void testPairEqualLen();
    void testPairDifferentLen();
public:
    TestDistance();
private:
    QString randomString(int size);
private:
    LevenshteinDistance testObj;
    static const int methodsToTest = 4;
    const int testsPerPair = 10;
    typedef int (LevenshteinDistance::*func)(QString, QString);
    func methodsPtr[methodsToTest] = {&LevenshteinDistance::levenshteinDistance_m,
                          &LevenshteinDistance::levenshteinDistance_r,
                          &LevenshteinDistance::damerauLevenshteinDistance_m,
                          &LevenshteinDistance::damerauLevenshteinDistance_r};
};

#endif // TESTDISTANCE_H
