#ifndef TESTSEARCH_H
#define TESTSEARCH_H

#include <QObject>
#include <QtTest/QtTest>

#include "search.h"

class TestSearch : public QObject
{
    Q_OBJECT
public:
    explicit TestSearch(QObject *parent = nullptr);
private slots:
    void testKMP();
private:
    vector<string> texts;
    vector<string> substrings;
    vector<int> indices;
};

#endif // TESTSEARCH_H
