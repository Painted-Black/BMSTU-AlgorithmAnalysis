#include "testdistance.h"

TestDistance::TestDistance()
{
    srand(time(nullptr));
}

void TestDistance::testEmptyString()
{
    for (int i = 0; i < methodsToTest; ++i)
    {
        QVERIFY((testObj.*methodsPtr[i])("", "") == 0);
        QVERIFY((testObj.*methodsPtr[i])("1", "") == 1);
        QVERIFY((testObj.*methodsPtr[i])("12", "") == 2);
        QVERIFY((testObj.*methodsPtr[i])("", "123456789") == 9);
    }
}

void TestDistance::testSameStrings()
{
    for (int i = 0; i < methodsToTest; ++i)
    {
        QVERIFY((testObj.*methodsPtr[i])("abc", "abc") == 0);
        QVERIFY((testObj.*methodsPtr[i])("ABC", "ABC") == 0);
        QVERIFY((testObj.*methodsPtr[i])("", "") == 0);
        QVERIFY((testObj.*methodsPtr[i])("a", "a") == 0);
    }
}

void TestDistance::testDifferentStrings()
{
    for (int i = 0; i < methodsToTest; ++i)
    {
        QVERIFY((testObj.*methodsPtr[i])("a", "") == 1);
        QVERIFY((testObj.*methodsPtr[i])("", "1") == 1);
        QVERIFY((testObj.*methodsPtr[i])("b", "c") == 1);
        QVERIFY((testObj.*methodsPtr[i])("bc", "b") == 1);
        QVERIFY((testObj.*methodsPtr[i])("bc", "c") == 1);
        QVERIFY((testObj.*methodsPtr[i])("ab", "cd") == 2);
        QVERIFY((testObj.*methodsPtr[i])("ab", "AB") == 2);
        QVERIFY((testObj.*methodsPtr[i])("Cd", "cd") == 1);

        QVERIFY((testObj.*methodsPtr[i])("скат", "кот") == 2);
        QVERIFY((testObj.*methodsPtr[i])("скат", "кат") == 1);
        QVERIFY((testObj.*methodsPtr[i])("скатскат", "скат") == 4);
        QVERIFY((testObj.*methodsPtr[i])("СКАТ", "скат") == 4);
        QVERIFY((testObj.*methodsPtr[i])("СкАт", "скат") == 2);
    }
}

void TestDistance::test_levenshteinDistance_m()
{
    QVERIFY(testObj.levenshteinDistance_m("ac", "ca") == 2);
    QVERIFY(testObj.levenshteinDistance_m("abc", "cba") == 2);
}

void TestDistance::test_levenshteinDistance_r()
{
    QVERIFY(testObj.levenshteinDistance_r("ac", "ca") == 2);
    QVERIFY(testObj.levenshteinDistance_r("abc", "cba") == 2);
}

void TestDistance::test_damerauLevenshteinDistance_m()
{
    QVERIFY(testObj.damerauLevenshteinDistance_m("ac", "ca") == 1);
    QVERIFY(testObj.damerauLevenshteinDistance_m("abc", "cba") == 2);
}

void TestDistance::test_damerauLevenshteinDistance_r()
{
    QVERIFY(testObj.damerauLevenshteinDistance_r("ac", "ca") == 1);
    QVERIFY(testObj.damerauLevenshteinDistance_r("abc", "cba") == 2);
}

void TestDistance::testPairsEmpty()
{
    for (int i = 0; i < testsPerPair; ++i)
    {
        QString s1 = "";
        QString s2 = randomString(i);
        QVERIFY(testObj.levenshteinDistance_m(s1, s2) == testObj.levenshteinDistance_r(s1, s2));
        QVERIFY(testObj.levenshteinDistance_m(s2, s1) == testObj.levenshteinDistance_r(s2, s1));
    }
}

void TestDistance::testPairEqualLen()
{
    for (int i = 0; i < testsPerPair; ++i)
    {
        QString s1 = randomString(i);
        QString s2 = randomString(i);
        QVERIFY(testObj.levenshteinDistance_m(s1, s2) == testObj.levenshteinDistance_r(s1, s2));
        QVERIFY(testObj.levenshteinDistance_m(s2, s1) == testObj.levenshteinDistance_r(s2, s1));
    }
}

void TestDistance::testPairDifferentLen()
{
    for (int i = 0; i < testsPerPair; ++i)
    {
        int l1 = 1 + rand() % 10;
        int l2 = 1 + rand() % 10;
        QString s1 = randomString(l1);
        QString s2 = randomString(l2);
        QVERIFY(testObj.levenshteinDistance_m(s1, s2) == testObj.levenshteinDistance_r(s1, s2));
        QVERIFY(testObj.levenshteinDistance_m(s2, s1) == testObj.levenshteinDistance_r(s2, s1));
    }
}

QString TestDistance::randomString(int size)
{
    string symbols = "abcdefghigklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVWXYZ1234567890";
    int symbolsSize = symbols.size();
    QString res = "";
    for (int i = 0; i < size; ++i)
    {
        res += symbols.at(rand() % (symbolsSize - 1));
    }
    return res;
}
