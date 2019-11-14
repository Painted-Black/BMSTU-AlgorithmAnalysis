#include "testmymatrix.h"

TestMyMatrix::TestMyMatrix(QObject *parent) : QObject(parent)
{

}

void TestMyMatrix::TestMultiplies()
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

    for (unsigned int i = 4; i < testMatrices1.size(); ++i)
    {
        {
            MyMatrix testMatrix1(testMatrices1.at(i));
            MyMatrix testMatrix2(testMatrices2.at(i));
            MyMatrix resMatrix(resMatrices.at(i));
            MyMatrix testRes = testMatrix1.multiplyVinograd(testMatrix2);
            bool res = resMatrix.isEqual(testRes);
            QVERIFY(res == true);
        }
        {
            for (int j = 1; j <= LOGIC_KERNELS * 4; ++j)
            {
                MyMatrix testMatrix1(testMatrices1.at(i));
                MyMatrix testMatrix2(testMatrices2.at(i));
                MyMatrix resMatrix(resMatrices.at(i));
                MyMatrix testRes = testMatrix1.multiplyVinograd_multithread(testMatrix2, 4);
                bool res = resMatrix.isEqual(testRes);
                QVERIFY(res == true);
            }
        }
    }
}

void TestMyMatrix::TestPairsSquare()
{
    srand(time(nullptr));
    for (int i = MIN_MATRIX_SIZE; i < MAX_MATRIX_SIZE; i += SIZE_STEP)
        for (int j = 0; j < TESTS_PER_SIZE; ++j)
        {
            for (int k = 1; k <= LOGIC_KERNELS * 4; ++k)
            {
                MyMatrix m1(i, i, true);
                MyMatrix m2(i, i, true);

                MyMatrix res1 = m1.multiplyVinograd(m2);
                MyMatrix res2 = m1.multiplyVinograd_multithread(m2, k);

                bool isEqu = res1.isEqual(res2);

                QVERIFY(isEqu == 1);
            }

        }
}

void TestMyMatrix::TestPairsNotSquare()
{
    srand(time(nullptr));
    for (int i = MIN_MATRIX_SIZE; i < MAX_MATRIX_SIZE; i += SIZE_STEP)
        for (int j = 0; j < TESTS_PER_SIZE; ++j)
        {
            int randNum = rand() % 10 + 1;
            for (int k = 1; k <= LOGIC_KERNELS * 4; ++k)
            {
                MyMatrix m1(i, i + randNum, true);
                MyMatrix m2(i + randNum, i, true);

                MyMatrix res1 = m1.multiplyVinograd(m2);
                MyMatrix res2 = m1.multiplyVinograd_multithread(m2, k);

                bool isEqu = res1.isEqual(res2);

                QVERIFY(isEqu == 1);
            }
        }
}

