#ifndef LEVENSHTEINDISTANCE_H
#define LEVENSHTEINDISTANCE_H

#include <iostream>
#include <QCoreApplication>

using namespace std;

class LevenshteinDistance
{
public:
    LevenshteinDistance() {}

    int levenshteinDistance_m(QString s1, QString s2);
    int levenshteinDistance_r(QString s1, QString s2);
    int damerauLevenshteinDistance_m(QString s1, QString s2);
    int damerauLevenshteinDistance_r(QString s1, QString s2);
    void setPrintMatrixFlag(bool value);

private:
    void printMatrix(int *m, int rows, int cols);
    int myMin(int v1, int v2, int v3);

private:
    bool printMatrixFlag = false;
};


#endif // LEVENSHTEINDISTANCE_H
