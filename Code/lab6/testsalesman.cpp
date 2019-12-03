#include "testsalesman.h"

TestSalesman::TestSalesman(QObject *parent) : QObject(parent)
{
    testFilenames.push_back(path + "small/test2");
    resFilenames.push_back(path + "small/res2");
    testFilenames.push_back(path + "small/test31");
    resFilenames.push_back(path + "small/res31");
    testFilenames.push_back(path + "small/test32");
    resFilenames.push_back(path + "small/res32");
    testFilenames.push_back(path + "small/test41");
    resFilenames.push_back(path + "small/res41");
    testFilenames.push_back(path + "small/test42");
    resFilenames.push_back(path + "small/res42");
    testFilenames.push_back(path + "small/test43");
    resFilenames.push_back(path + "small/res43");
    testFilenames.push_back(path + "small/test44");
    resFilenames.push_back(path + "small/res44");
    testFilenames.push_back(path + "small/test45");
    resFilenames.push_back(path + "small/res45");
    testFilenames.push_back(path + "/small/test51");
    resFilenames.push_back(path + "small/res51");
    testFilenames.push_back(path + "small/test52");
    resFilenames.push_back(path + "small/res52");
    testFilenames.push_back(path + "small/test53");
    resFilenames.push_back(path + "small/res53");
    testFilenames.push_back(path + "small/test54");
    resFilenames.push_back(path + "small/res54");

    compareFilenames.push_back(path + "medium/test61");
    compareResFilenames.push_back(path + "medium/res61");
    compareFilenames.push_back(path + "medium/test62");
    compareResFilenames.push_back(path + "medium/res62");

    testsTotal = static_cast<unsigned int>(testFilenames.size());
    comparesTotal = static_cast<unsigned int>(compareFilenames.size());

    for (unsigned int i = 0; i < testsTotal; ++i)
    {
        ifstream fout(resFilenames.at(i));
        if (fout.is_open())
        {
            int res;
            fout >> res;
            results.push_back(res);
        }
        else
        {
            cout << "Невозможно открыть файл " << testFilenames.at(i) << endl;
            results.push_back(-1);
        }
        fout.close();
    }

    for (unsigned int i = 0; i < comparesTotal; ++i)
    {
        ifstream fout(compareResFilenames.at(i));
        if (fout.is_open())
        {
            int res;
            fout >> res;
            results.push_back(res);
        }
        else
        {
            cout << "Невозможно открыть файл " << compareResFilenames.at(i) << endl;
            compareResults.push_back(-1);
        }
        fout.close();
    }
}

void TestSalesman::testBruteForce()
{
    for (int i = 0; i < testsTotal; ++i)
    {
        AdjacencyMatrix am(testFilenames.at(i));
        BruteForce bf;
        int routeLen = bf.getMinRoute(&am);
        QVERIFY(routeLen == results.at(i));
    }
}

void TestSalesman::testAntColony()
{
    for (unsigned int i = 0; i < testsTotal; ++i)
    {
        AdjacencyMatrix am(testFilenames.at(i));
        AntColony ac;
        int routeLen = ac.getMinRoute(&am, 1, 9, 0.1, 100);
        QVERIFY(routeLen == results.at(i));
    }
}

void TestSalesman::compare()
{
    for (unsigned int i = 0; i < comparesTotal; ++i)
    {
        AdjacencyMatrix am(compareFilenames.at(i));
        AntColony ac;
        BruteForce bf;
        int acRouteLen = ac.getMinRoute(&am, 1, 9, 0.1, 100);
        int bfRouteLen = bf.getMinRoute(&am);
        QCOMPARE(acRouteLen, bfRouteLen);
    }
}
