#include "testmymatrix.h"

TestMyMatrix::TestMyMatrix(QObject *parent) : QObject(parent)
{

}

void TestMyMatrix::testMultiplies(func f)
{
    std::vector<std::initializer_list<std::initializer_list<int>>> testMatrices1 =
    {{{0}},
     {{0}},
     {{1}},
     {{2}},
     {{1, 1},{1, 1}},
     {{2, 2},{2, 2}},
     {{0, 0},{0, 0}},
     {{0, 0},{0, 0}},
     {{1, 2},{3, 4}},
     {{1, 1},{1, 1}},
     {{1, 2},{3, 4}},

     {{1}, {1}},
     {{1, 1}},

     {{1, 2}, {3, 4}, {5, 6}},
     {{1, 4, 8}, {16, 32, 64}},
     {{1, 4, 1}, {5, 9, 2}, {6, 5, 3}, {5, 8, 9}}};
    std::vector<std::initializer_list<std::initializer_list<int>>> testMatrices2 =
    {{{0}},
     {{1}},
     {{1}},
     {{2}},
     {{1, 1},{1, 1}},
     {{2, 2},{2, 2}},
     {{0, 0},{0, 0}},
     {{1, 1},{1, 1}},
     {{1, 1},{1, 1}},
     {{1, 2},{3, 4}},
     {{1, 2},{3, 4}},

     {{1, 1}},
     {{1}, {1}},

     {{6, 5, 4}, {3, 2, 1}},
     {{1, 3}, {9, 27}, {81, 243}},
     {{7, 9, 3, 2}, {3, 8, 4, 6}, {2, 6, 4, 3}}};
    std::vector<std::initializer_list<std::initializer_list<int>>> resMatrices =
    {{{0}},
     {{0}},
     {{1}},
     {{4}},
     {{2, 2}, {2, 2}},
     {{8, 8},{8, 8}},
     {{0, 0},{0, 0}},
     {{0, 0},{0, 0}},
     {{3, 3},{7, 7}},
     {{4, 6},{4, 6}},
     {{7, 10},{15, 22}},

     {{1, 1}, {1, 1}},
     {{2}},

     {{12, 9, 6}, {30, 23, 16}, {48, 37, 26}},
     {{685, 2055}, {5488, 16464}},
     {{21, 47, 23, 29}, {66, 129, 59, 70}, {63, 112, 50, 51}, {77, 163, 83, 85}}};

    for (unsigned int i = 0; i < testMatrices1.size(); ++i)
    {
        MyMatrix testMatrix1(testMatrices1.at(i));
        MyMatrix testMatrix2(testMatrices2.at(i));
        MyMatrix resMatrix(resMatrices.at(i));
        MyMatrix testRes = (testMatrix1.*f)(testMatrix2);
        bool res = resMatrix.isEqual(testRes);
        QVERIFY(res == true);
    }
}

void TestMyMatrix::TestMultiply()
{
    testMultiplies(&MyMatrix::multiply);
}

void TestMyMatrix::TestMultiplyVinograd()
{
    testMultiplies(&MyMatrix::multiplyVinograd);
}

void TestMyMatrix::TestMultiplyVinogradOptimized()
{
    testMultiplies(&MyMatrix::multiplyVinogradOptimized);
}

void TestMyMatrix::TestPairsSquare()
{
    srand(time(nullptr));
    for (int i = MIN_MATRIX_SIZE; i < MAX_MATRIX_SIZE; i += SIZE_STEP)
        for (int j = 0; j < TESTS_PER_SIZE; ++j)
        {
            MyMatrix m1(i, i, true);
            MyMatrix m2(i, i, true);
            MyMatrix m1_copy(m1);
            MyMatrix m2_copy(m2);

            MyMatrix m1_copy2(m1);
            MyMatrix m2_copy2(m2);

            MyMatrix res1 = m1.multiply(m2);
            MyMatrix res2 = m1_copy.multiplyVinograd(m2_copy);
            MyMatrix res3 = m1_copy2.multiplyVinogradOptimized(m2_copy2);

            bool res = res1.isEqual(res2, res3);
            QVERIFY(res == true);
        }
}

void TestMyMatrix::TestPairsNotSquare()
{
    srand(time(nullptr));
    for (int i = MIN_MATRIX_SIZE; i < MAX_MATRIX_SIZE; i += SIZE_STEP)
        for (int j = 0; j < TESTS_PER_SIZE; ++j)
        {
            int randNum = rand() % 10 + 1;
            MyMatrix m1(i, i + randNum, true);
            MyMatrix m2(i + randNum, i, true);
            MyMatrix m1_copy(m1);
            MyMatrix m2_copy(m2);

            MyMatrix m1_copy2(m1);
            MyMatrix m2_copy2(m2);

            MyMatrix res1 = m1.multiply(m2);
            MyMatrix res2 = m1_copy.multiplyVinograd(m2_copy);
            MyMatrix res3 = m1_copy2.multiplyVinogradOptimized(m2_copy2);

            bool res = res1.isEqual(res2, res3);
            QVERIFY(res == true);
        }
}

