#include <QCoreApplication>
#include <QDebug>

#include <sstream>
#include <fstream>
#include <string>
#include <time.h>

#include "mymatrix.h"
#include "testmymatrix.h"

using namespace std;

void menu(int argc, char *argv[]);
void inputVinograd();
void inputVinogradParallel();
void timeTests();
void writeVectorsToFile(ofstream &fout, string message, vector<string>);

const string FILENAME = "../times";

int START_SIZE = 101;
int END_SIZE = 1001;
int STEP = 100;
int TESTS_PER_SIZE = 1;

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
        cout << "1 - умножение двух матриц алгоритмом Винограда" << endl
             << "2 - умножение двух матриц параллельным алгоритмом Винограда" << endl
             << "3 - тесты" << endl
             << "4 - временной анализ" << endl
             << " > ";
        string saction;
        cin >> saction;
        istringstream iss (saction, istringstream::in);
        int action;
        iss >> action;

        switch (action)
        {
            case 1:
                inputVinograd();
                break;
            case 2:
                inputVinogradParallel();
                break;
            case 3:
                QTest::qExec(&testMyMatrix, argc, argv);
                break;
            case 4:
                timeTests();
                break;
            default:
                run = false;
        }
    }
}

void inputVinograd()
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
        MyMatrix m3 = m1.multiplyVinograd(m2);
        m3.print();
    } catch (logic_error) {
        cout << "Невозможно умножить такие матрицы." << endl;
    }
}

void inputVinogradParallel()
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

    int threads;
    cout << "Threads: ";
    cin >> threads;

    cout << "m1 * m2:" << endl;

    try {
        MyMatrix m3 = m1.multiplyVinograd_multithread(m2, threads);
        m3.print();
    } catch (logic_error) {
        cout << "Невозможно умножить такие матрицы." << endl;
    }
}


void timeTests()
{
    vector<string> times;
    QTime timer;
    for (int i = START_SIZE; i <= END_SIZE; i += STEP)
    {
        int totalTime = 0;
        string res = to_string(i) + " & ";;
        for (int j = 0; j < TESTS_PER_SIZE; ++j)
        {
            MyMatrix m1(i, i, true);
            MyMatrix m2(i, i, true);

            timer.restart();
            MyMatrix m3 = m1.multiplyVinograd(m2);
            totalTime += timer.elapsed();
        }
        totalTime /= TESTS_PER_SIZE;
        res += to_string(totalTime) + " & ";

        for (int j = 1; j <= 16; ++j)
        {
            totalTime = 0;
            for (int k = 0; k < TESTS_PER_SIZE; ++k)
            {
                MyMatrix m1(i, i, true);
                MyMatrix m2(i, i, true);

                timer.restart();
                MyMatrix m3 = m1.multiplyVinograd_multithread(m2, j);
                totalTime += timer.elapsed();
            }
            totalTime /= TESTS_PER_SIZE;
            res += to_string(totalTime) + " & ";
        }
        times.push_back(res);
    }

    ofstream fout(FILENAME);
    if (fout.is_open())
    {
        writeVectorsToFile(fout, "Четные", times);
        cout << "Результаты записаны в файл: " << FILENAME << endl;
    }
    else
        cout << "Невозможно открыть файл " << FILENAME << endl;
    fout.close();
}

void writeVectorsToFile(ofstream &fout, string message, vector<string> v)
{
    fout.precision(10);
    fout.setf(ios::fixed);
    fout << message << endl;
    fout << "Размер массива\t" << "0, 1, ... 16" << endl;
    for (int i = 0; i < v.size(); ++i)
    {
        fout << v.at(i) << endl;
    }
}
