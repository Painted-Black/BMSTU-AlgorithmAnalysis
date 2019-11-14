#include "testmyarray.h"

TestMyArray::TestMyArray() : QObject()
{
    srand(time(nullptr));
}

void TestMyArray::testSameElements()
{
    std::vector<std::vector<int>> testArrays = {std::vector<int>{1, 1},
                                                std::vector<int>{1},
                                                std::vector<int>{1, 1, 1},
                                                std::vector<int>{-1, -1}};
    std::vector<std::vector<int>> resultArrays = {std::vector<int>{1, 1},
                                                 std::vector<int>{1},
                                                 std::vector<int>{1, 1, 1},
                                                 std::vector<int>{-1, -1}};
    for (int i = 0; i < testArrays.size(); ++i)
    {
        {
            MyArray testArray(testArrays.at(i));
            MyArray resultArray(resultArrays.at(i));
            testArray.insertionSort();
            bool res = resultArray.compare(testArray);
            QVERIFY(res == 1);
        }
        {
            MyArray testArray(testArrays.at(i));
            MyArray resultArray(resultArrays.at(i));
            testArray.bubbleSort();
            bool res = resultArray.compare(testArray);
            QVERIFY(res == 1);
        }
        {
            MyArray testArray(testArrays.at(i));
            MyArray resultArray(resultArrays.at(i));
            testArray.quickSort(0, testArray.getSize() - 1);
            bool res = resultArray.compare(testArray);
            QVERIFY(res == 1);
        }
    }
}

void TestMyArray::testDifferentPositiveElements()
{
    std::vector<std::vector<int>> testArrays = {std::vector<int>{1, 2, 3},
                                                std::vector<int>{3, 2, 1},
                                                std::vector<int>{1, 2, 1},
                                                std::vector<int>{2, 2, 1},
                                                std::vector<int>{1, 1, 2},
                                                std::vector<int>{1, 1, 2, 2},
                                                std::vector<int>{1, 2, 1, 2},
                                                std::vector<int>{2, 2, 1, 1},
                                                std::vector<int>{2, 1, 2, 1}};
    std::vector<std::vector<int>> resultArrays = {std::vector<int>{1, 2, 3},
                                                  std::vector<int>{1, 2, 3},
                                                  std::vector<int>{1, 1, 2},
                                                  std::vector<int>{1, 2, 2},
                                                  std::vector<int>{1, 1, 2},
                                                  std::vector<int>{1, 1, 2, 2},
                                                  std::vector<int>{1, 1, 2, 2},
                                                  std::vector<int>{1, 1, 2, 2},
                                                  std::vector<int>{1, 1, 2, 2}};
    for (int i = 0; i < testArrays.size(); ++i)
    {
        {
            MyArray testArray(testArrays.at(i));
            MyArray resultArray(resultArrays.at(i));
            testArray.insertionSort();
            bool res = resultArray.compare(testArray);
            QVERIFY(res == 1);
        }
        {
            MyArray testArray(testArrays.at(i));
            MyArray resultArray(resultArrays.at(i));
            testArray.bubbleSort();
            bool res = resultArray.compare(testArray);
            QVERIFY(res == 1);
        }
        {
            MyArray testArray(testArrays.at(i));
            MyArray resultArray(resultArrays.at(i));
            testArray.quickSort(0, testArray.getSize() - 1);
            bool res = resultArray.compare(testArray);
            QVERIFY(res == 1);
        }
    }
}

void TestMyArray::testDifferentNegativeElements()
{
    std::vector<std::vector<int>> testArrays = {std::vector<int>{-1, -2, -3},
                                                std::vector<int>{-3, -2, -1},
                                                std::vector<int>{-1, -2, -1},
                                                std::vector<int>{-2, -2, -1},
                                                std::vector<int>{-1, -1, -2},
                                                std::vector<int>{-1, -1, -2, -2},
                                                std::vector<int>{-1, -2, -1, -2},
                                                std::vector<int>{-2, -2, -1, -1},
                                                std::vector<int>{-2, -1, -2, -1}};
    std::vector<std::vector<int>> resultArrays = {std::vector<int>{-3, -2, -1},
                                                  std::vector<int>{-3, -2, -1},
                                                  std::vector<int>{-2, -1, -1},
                                                  std::vector<int>{-2, -2, -1},
                                                  std::vector<int>{-2, -1, -1},
                                                  std::vector<int>{-2, -2, -1, -1},
                                                  std::vector<int>{-2, -2, -1, -1},
                                                  std::vector<int>{-2, -2, -1, -1},
                                                  std::vector<int>{-2, -2, -1, -1}};
    for (int i = 0; i < testArrays.size(); ++i)
    {
        {
            MyArray testArray(testArrays.at(i));
            MyArray resultArray(resultArrays.at(i));
            testArray.insertionSort();
            bool res = resultArray.compare(testArray);
            QVERIFY(res == 1);
        }
        {
            MyArray testArray(testArrays.at(i));
            MyArray resultArray(resultArrays.at(i));
            testArray.bubbleSort();
            bool res = resultArray.compare(testArray);
            QVERIFY(res == 1);
        }
        {
            MyArray testArray(testArrays.at(i));
            MyArray resultArray(resultArrays.at(i));
            testArray.quickSort(0, testArray.getSize() - 1);
            bool res = resultArray.compare(testArray);
            QVERIFY(res == 1);
        }
    }
}

void TestMyArray::testDifferentElements()
{
    std::vector<std::vector<int>> testArrays = {std::vector<int>{-1, 2, 3},
                                                std::vector<int>{-1, -2, 3},
                                                std::vector<int>{-1, 2, -1},
                                                std::vector<int>{-2, -2, 1},
                                                std::vector<int>{-1, 1, -2},

                                                std::vector<int>{-1, 0, 2},
                                                std::vector<int>{2, 0, -1},
                                                std::vector<int>{0, -1, 2},
                                                std::vector<int>{2, -1, 0},

                                                std::vector<int>{-1, 1, -2, 2},
                                                std::vector<int>{-1, 2, -1, 2},
                                                std::vector<int>{-2, -2, 1, 1},
                                                std::vector<int>{2, -1, -2, -1}};
    std::vector<std::vector<int>> resultArrays = {std::vector<int>{-1, 2, 3},
                                                  std::vector<int>{-2, -1, 3},
                                                  std::vector<int>{-1, -1, 2},
                                                  std::vector<int>{-2, -2, 1},
                                                  std::vector<int>{-2, -1, 1},

                                                  std::vector<int>{-1, 0, 2},
                                                  std::vector<int>{-1, 0, 2},
                                                  std::vector<int>{-1, 0, 2},
                                                  std::vector<int>{-1, 0, 2},

                                                  std::vector<int>{-2, -1, 1, 2},
                                                  std::vector<int>{-1, -1, 2, 2},
                                                  std::vector<int>{-2, -2, 1, 1},
                                                  std::vector<int>{-2, -1, -1, 2}};
    for (int i = 0; i < testArrays.size(); ++i)
    {
        {
            MyArray testArray(testArrays.at(i));
            MyArray resultArray(resultArrays.at(i));
            testArray.insertionSort();
            bool res = resultArray.compare(testArray);
            QVERIFY(res == 1);
        }
        {
            MyArray testArray(testArrays.at(i));
            MyArray resultArray(resultArrays.at(i));
            testArray.bubbleSort();
            bool res = resultArray.compare(testArray);
            QVERIFY(res == 1);
        }
        {
            MyArray testArray(testArrays.at(i));
            MyArray resultArray(resultArrays.at(i));
            testArray.quickSort(0, testArray.getSize() - 1);
            bool res = resultArray.compare(testArray);
            QVERIFY(res == 1);
        }
    }
}

void TestMyArray::compareSortingsResults()
{
    for (int vecSize = 0; vecSize < 100; vecSize += 10)
    {
        for (int testsPerSize = 0; testsPerSize < 1; ++testsPerSize)
        {
            std::vector<int> randVec = randomVector(vecSize);
            MyArray testInsertion(randVec);
            MyArray testQsort(randVec);
            MyArray testBubble(randVec);
            testInsertion.insertionSort();
            testQsort.quickSort(0, testQsort.getSize() - 1);
            testBubble.bubbleSort();
            bool res = testInsertion.compare(testQsort, testBubble);
            QVERIFY(res == 1);
        }
    }
}

std::vector<int> TestMyArray::randomVector(int size, int minValue, int range)
{
    std::vector<int> vec;
    for (int i = 0; i < size; ++i)
    {
        int randInt = range + rand() % minValue;
        vec.push_back(randInt);
    }
    return vec;
}
