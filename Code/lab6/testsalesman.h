#ifndef TESTSALESMAN_H
#define TESTSALESMAN_H

#include <iostream>
#include <string>
#include "fstream"

#include <QObject>
#include <QtTest/QtTest>

#include "adjacencymatrix.h"
#include "bruteforce.h"
#include "antcolony.h"

using namespace std;

class TestSalesman : public QObject
{
    Q_OBJECT
public:
    explicit TestSalesman(QObject *parent = nullptr);
private slots:
    void testBruteForce();
    void testAntColony();
    void compare();
private:
    vector<string> testFilenames;
    vector<string> resFilenames;

    vector<string> compareFilenames;
    vector<string> compareResFilenames;

    vector<int> results;
    vector<int> compareResults;


    unsigned int testsTotal;
    unsigned int comparesTotal;

    string path = "/home/syzygy/lab6_aa/tests/";
};

#endif // TESTSALESMAN_H
