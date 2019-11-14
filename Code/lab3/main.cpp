#include <QCoreApplication>
#include <sstream>
#include <time.h>
#include <string>
#include <fstream>

#include "myarray.h"
#include "testmyarray.h"

using namespace std;

void menu(int argc, char * argv[]);
void randomInsertionSort();
void randomQSort();
void randomBubbleSort();
int getArrayLen();
void timeTests();
void timeTestArrays(string message, ofstream &fout);
void writeVectorsToFile(ofstream &fout, string message,
                        vector<double> v1, vector<double> v2, vector<double> v3);
MyArray qsortBestGenerator(int size);

const int TESTS_PER_ARRAY_SIZE = 100;
const int MIN_TEST_ARRAY_LEN = 0;
const int MAX_TEST_ARRAY_LEN = 2000;
const int ARRAY_LEN_STEP = 100;
const string FILENAME = "../times";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    MyArray arr(20);
//    arr.randomize();
//    arr.insertionSort();
//    arr.print();
    menu(argc, argv);

    return 0;
}

void menu(int argc, char * argv[])
{
    TestMyArray testMyArray;
    bool run = true;
    while (run)
    {
        cout << "1 - сортировка случайного масива с помощью алгоритма сортировки вставками" << endl
             << "2 - сортировка случайного масива с помощью алгоритма сортировки пузырьком" << endl
             << "3 - сортировка случайного масива с помощью алгоритма быстрой сортировки" << endl
             << "4 - временной анализ" << endl
             << "5 - тесты" << endl
             << " > ";
        string saction;
        cin >> saction;
        istringstream iss (saction, istringstream::in);
        int action;
        iss >> action;

        switch (action)
        {
            case 1:
                randomInsertionSort();
                break;
            case 2:
                randomBubbleSort();
                break;
            case 3:
                randomQSort();
                break;
            case 4:
                timeTests();
                break;
            case 5:
                QTest::qExec(&testMyArray, argc, argv);
                break;
            default:
                run = false;
        }
    }
}

void timeTests()
{
    ofstream fout(FILENAME);
    if (fout.is_open())
    {
        timeTestArrays("Сортировка быстрая", fout);
        cout << "Результаты записаны в файл: " << FILENAME << endl;
    }
    fout.close();

}

MyArray qsortBestGenerator(int size)
{
    MyArray arr(size);
    for (int i = 0, j = 700; i < size / 2; ++i, --j)
    {
        arr.insert(2, j);
    }
    return arr;
}

void timeTestArrays(string message, ofstream &fout)
{
    // Тестируем массивы, заполненные одинаковыми числами
    vector<double> insertionBest;
    vector<double> insertionAvg;
    vector<double> insertionWorst;
    for (int i = MIN_TEST_ARRAY_LEN; i <= MAX_TEST_ARRAY_LEN; i += ARRAY_LEN_STEP)
    {
        MyArray arrayBest(i);
//        MyArray arrayBest = qsortBestGenerator(i);
//        arrayBest.insertionSort();
        MyArray arrayAvg(i);
        arrayAvg.randomize();
        MyArray arrayWorst(i);
        arrayWorst.randomize();
        arrayWorst.insertionSortDescending();

        clock_t t1, t2;
        double totalTicksBest = 0, totalTicksAvg = 0, totalTicksWorst = 0;
        for (int j = 0; j < TESTS_PER_ARRAY_SIZE; ++j)
        {
            t1 = clock();
            arrayBest.quickSort(0, arrayBest.getSize());
            t2 = clock();
            totalTicksBest += (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC);

            t1 = clock();
            arrayAvg.quickSort(0, arrayBest.getSize());
            t2 = clock();
            totalTicksAvg += (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC);

            t1 = clock();
            arrayWorst.quickSort(0, arrayBest.getSize());
            t2 = clock();
            totalTicksWorst += (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC);
        }
        totalTicksBest /= TESTS_PER_ARRAY_SIZE;
        insertionBest.push_back(totalTicksBest);

        totalTicksAvg /= TESTS_PER_ARRAY_SIZE;
        insertionAvg.push_back(totalTicksAvg);

        totalTicksWorst /= TESTS_PER_ARRAY_SIZE;
        insertionWorst.push_back(totalTicksWorst);
    }
    writeVectorsToFile(fout, message, insertionBest, insertionAvg, insertionWorst);
}

void writeVectorsToFile(ofstream &fout, string message, vector<double> v1, vector<double> v2, vector<double> v3)
{
    fout.precision(10);
    fout.setf(ios::fixed);
    fout << message << endl;
    fout << "Размер массива\t" << "Лучший\t" << "Средний\t" << "Худший\t" << endl;
    for (int i = 0; i < v1.size(); ++i)
    {
//        fout << i * ARRAY_LEN_STEP << " " << v3.at(i) << endl;
        fout << i * ARRAY_LEN_STEP << " & " << v1.at(i) << " & "
             << v2.at(i) << " & "
             << v3.at(i) << " \\\\" << endl
             << "\\hline" << endl;
    }
}

void randomInsertionSort()
{
    int arrSize = getArrayLen();
    MyArray array(arrSize);
    array.randomize();
    cout << endl;
    cout << "Исходный массив: " << endl;
    array.print();
    array.insertionSort();
    cout << "Отсортированный массив: " << endl;
    array.print();
    cout << endl;
}

void randomQSort()
{
    int arrSize = getArrayLen();
    MyArray array(arrSize);
    array.randomize();
    cout << endl;
    cout << "Исходный массив: " << endl;
    array.print();
    array.quickSort(0, array.getSize() - 1);
    cout << "Отсортированный массив: " << endl;
    array.print();
    cout << endl;
}

void randomBubbleSort()
{
    int arrSize = getArrayLen();
    MyArray array(arrSize);
    array.randomize();
    cout << endl;
    cout << "Исходный массив: " << endl;
    array.print();
    array.bubbleSort();
    cout << "Отсортированный массив: " << endl;
    array.print();
    cout << endl;
}

int getArrayLen()
{
    string str_size;
    int size = -1;
    while (size < 0)
    {
        cout << "Введите длину массива: " << endl;
        cin >> str_size;
        try {

            size = stoi(str_size);
        } catch (invalid_argument) {
            cout << "Некорректный ввод, попробуйте еще раз." << endl;
        }
    }
    return size;
}
