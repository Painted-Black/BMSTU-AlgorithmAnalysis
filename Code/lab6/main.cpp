#include <QCoreApplication>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

#include "adjacencymatrix.h"
#include "bruteforce.h"
#include "testsalesman.h"
#include "antcolony.h"

#include "ant.h"

using namespace std;

static string FILENAME = "/home/syzygy/lab6_aa/amatrix";
static string PARA_FILENAME = "/home/syzygy/lab6_aa/para";

void parametrization();

int main(int argc, char *argv[])
{
    vector<int> m = vector<int>(0);
//    QCoreApplication a(argc, argv);

//    AdjacencyMatrix am(FILENAME);
//    BruteForce bf;
//    int routeLen = bf.getMinRoute(&am);
//    cout << routeLen << endl;

//    TestSalesman testSalesman;
//    QTest::qExec(&testSalesman, argc, argv);

    parametrization();

    return 0;
}

void parametrization()
{
    vector<size_t> alphas = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<double> qs = {0.1, 0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.75, 0.8, 0.9};
    vector<size_t> tmax = {5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    size_t alphaPlusBeta = 10;
//    vector<int> antResults;

    vector<int> bruteResults = {225, 240, 235};
    vector<double> bruteTimes;
//    double start, end;

    AdjacencyMatrix am1("/home/syzygy/lab6_aa/tests/parameterization/matrix1");
    AdjacencyMatrix am2("/home/syzygy/lab6_aa/tests/parameterization/matrix2");
    AdjacencyMatrix am3("/home/syzygy/lab6_aa/tests/parameterization/matrix3");

    BruteForce bf = BruteForce();

//    start = clock();
//    int bruteRoute = bf.getMinRoute(&am1);
//    end = double(clock() - start)/CLOCKS_PER_SEC;
//    bruteTimes.push_back(end);
//    bruteResults.push_back(bruteRoute);

//    start = clock();
//    bruteRoute = bf.getMinRoute(&am2);
//    end = double(clock() - start)/CLOCKS_PER_SEC;
//    bruteTimes.push_back(end);
//    bruteResults.push_back(bruteRoute);

//    start = clock();
//    bruteRoute = bf.getMinRoute(&am3);
//    end = double(clock() - start)/CLOCKS_PER_SEC;
//    bruteTimes.push_back(end);
//    bruteResults.push_back(bruteRoute);
//    cout << "Brute Force passed" << endl;

    ofstream fout(PARA_FILENAME);
    if (fout.is_open())
    {
        fout << "10 x 10" << endl;
        fout << "alpha & beta & q & tmax" << endl;
        for (size_t time = 0; time < tmax.size(); time++)
            for (size_t alpha = 0; alpha < alphas.size(); alpha++)
                for (size_t isp = 0; isp < qs.size(); isp++)
                {
                    AntColony ac = AntColony();
                    int antRoute1 = ac.getMinRoute(&am1, alphas[alpha], alphaPlusBeta - alphas[alpha], qs[isp], tmax[time]);
                    int antRoute2 = ac.getMinRoute(&am2, alphas[alpha], alphaPlusBeta - alphas[alpha], qs[isp], tmax[time]);
                    int antRoute3 = ac.getMinRoute(&am3, alphas[alpha], alphaPlusBeta - alphas[alpha], qs[isp], tmax[time]);
                    if ((bruteResults.at(0) >= antRoute1 - 5) &&
                        (bruteResults.at(0) <= antRoute1 + 5) &&
                        (bruteResults.at(1) >= antRoute2 - 5) &&
                        (bruteResults.at(1) <= antRoute2 + 5) &&
                        (bruteResults.at(2) >= antRoute3 - 5) &&
                        (bruteResults.at(2) <= antRoute3 + 5))
                    {
                        fout << " матрица1  "
                             << bruteResults.at(0) << "  "
                             << antRoute1 << "  "
                             << alphas[alpha] << " & "
                             << alphaPlusBeta - alphas[alpha] << " & "
                             << qs[isp] << " & "
                             << tmax[time]
                             << " \\\\"
                             << endl;
                        fout << " матрица2  "
                             << bruteResults.at(1) << "  "
                             << antRoute2 << "  "
                             << alphas[alpha] << " & "
                             << alphaPlusBeta - alphas[alpha] << " & "
                             << qs[isp] << " & "
                             << tmax[time]
                             << " \\\\"
                             << endl;
                        fout << " матрица3  "
                             << bruteResults.at(2) << "  "
                             << antRoute3 << "  "
                             << alphas[alpha] << " & "
                             << alphaPlusBeta - alphas[alpha] << " & "
                             << qs[isp] << " & "
                             << tmax[time]
                             << " \\\\"
                             << endl;
                    }
//                    if (bruteResults.at(0) == antRoute1)
//                    {
//                        fout << " матрица1  "
//                             << bruteResults.at(0)
//                             << antRoute1
//                             << alphas[alpha] << " & "
//                             << alphaPlusBeta - alphas[alpha] << " & "
//                             << qs[isp] << " & "
//                             << tmax[time] << " & "
//                             << " \\\\"
//                             << endl;
//                    }
//                    if (bruteResults.at(1) == antRoute2)
//                    {
//                        fout << " матрица2  "
//                             << bruteResults.at(1)
//                             << antRoute2
//                             << alphas[alpha] << " & "
//                             << alphaPlusBeta - alphas[alpha] << " & "
//                             << qs[isp] << " & "
//                             << tmax[time] << " & "
//                             << " \\\\"
//                             << endl;
//                    }
//                    if (bruteResults.at(2) == antRoute3)
//                    {
//                        fout << " матрица3  "
//                             << bruteResults.at(2)
//                             << antRoute3
//                             << alphas[alpha] << " & "
//                             << alphaPlusBeta - alphas[alpha] << " & "
//                             << qs[isp] << " & "
//                             << tmax[time] << " & "
//                             << " \\\\"
//                             << endl;
//                    }
                }
    }
    else
        cout << "Невозможно открыть файл " << PARA_FILENAME << endl;
}


