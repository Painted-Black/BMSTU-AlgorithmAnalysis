#include <QCoreApplication>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "mymatrix.h"
#include "testmymatrix.h"

using namespace std;

const string FILENAME = "../times";
const int MIN_SIZE = 101;
const int MAX_SIZE = 201;
const int STEP = 100;
const int TESTS_PER_SIZE = 1;

void timeTest();
void writeVectorsToFile(ofstream &fout, string message, vector<double> v,
                        vector<double> v2, vector<double> v3);
void input();
void menu(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    menu(argc, argv);
    return 0;
}

void menu(int argc, char *argv[])
{
    TestMyMatrix testMyMatrix;
    bool run = true;
    while (run)
    {
        cout << "1 - умножение двух матриц" << endl
             << "2 - тесты" << endl
             << "3 - временной анализ" << endl
             << " > ";
        string saction;
        cin >> saction;
        istringstream iss (saction, istringstream::in);
        int action;
        iss >> action;

        switch (action)
        {
            case 1:
                input();
                break;
            case 2:
                QTest::qExec(&testMyMatrix, argc, argv);
                break;
            case 3:
                timeTest();
                break;
            default:
                run = false;
        }
    }
}

void input()
{
    int r1, c1;
    cout << "Rows1: ";
    cin >> r1;
    cout << "Columns1: ";
    cin >> c1;

    int r2, c2;
    cout << "Rows2: ";
    cin >> r2;
    cout << "Columns2: ";
    cin >> c2;

    MyMatrix m1(r1, c1, true);
    MyMatrix m2(r2, c2, true);

    m1.print();
    cout << endl;
    m2.print();

    cout << "m1 * m2:" << endl;

    try {
        MyMatrix m3 = m1.multiply(m2);
        m3.print();
    } catch (logic_error) {
        cout << "Невозможно умножить такие матрицы." << endl;
    }
}

void timeTest()
{
    vector<double> timesClassic;
    vector<double> timesVinograd;
    vector<double> timesOpt;
    for (int i = MIN_SIZE; i <= MAX_SIZE; i += STEP)
    {
        clock_t t1, t2;
        double totalTicksClassic = 0, totalTicksVinograd, totalTicksOpt;
        for (int j = 0; j < TESTS_PER_SIZE; ++j)
        {
            {
                MyMatrix m1(i, i, true);
                MyMatrix m2(i, i, true);

                t1 = clock();
                MyMatrix m3 = m1.multiply(m2);
                t2 = clock();
                totalTicksClassic += (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC);
            }
            {
                MyMatrix m1(i, i, true);
                MyMatrix m2(i, i, true);

                t1 = clock();
                MyMatrix m3 = m1.multiplyVinograd(m2);
                t2 = clock();
                totalTicksVinograd += (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC);
            }
            {
                MyMatrix m1(i, i, true);
                MyMatrix m2(i, i, true);

                t1 = clock();
                MyMatrix m3 = m1.multiplyVinogradOptimized(m2);
                t2 = clock();
                totalTicksOpt += (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC);
            }
        }
        totalTicksClassic /= TESTS_PER_SIZE;
        timesClassic.push_back(totalTicksClassic);

        totalTicksVinograd /= TESTS_PER_SIZE;
        timesVinograd.push_back(totalTicksVinograd);

        totalTicksOpt /= TESTS_PER_SIZE;
        timesOpt.push_back(totalTicksOpt);
    }
    ofstream fout(FILENAME);
    if (fout.is_open())
    {
        writeVectorsToFile(fout, "Нечетный", timesClassic, timesVinograd, timesOpt);
        cout << "Результаты записаны в файл: " << FILENAME << endl;
    }
    else
        cout << "Невозможно открыть файл " << FILENAME << endl;
    fout.close();
}

void writeVectorsToFile(ofstream &fout, string message, vector<double> v1,
                        vector<double> v2, vector<double> v3)
{
    fout.precision(10);
    fout.setf(ios::fixed);
    fout << message << endl;
    fout << "Размер массива\t" << "Класс.\t" << "Виноград\t" << "Опт. Виноград\t" << endl;
    for (int i = 0; i < v1.size(); ++i)
    {
//        fout << i * ARRAY_LEN_STEP << " " << v3.at(i) << endl;
        fout << (i + 1) * STEP << " & " << v1.at(i) << " & "
             << v2.at(i) << " & "
             << v3.at(i) << " \\\\ "
             << "\\hline" << endl;
    }
}
