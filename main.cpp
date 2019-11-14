#include <QCoreApplication>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <time.h>

#include "levenshteindistance.h"
#include "testdistance.h"

using namespace std;

unsigned long long getTicks();
void menu(int argc, char * argv[]);
bool getPrintFlag();
void getDistanceMatrix(int (* func) (QString, QString, bool), bool);
void getDistanceRec(int (* func) (QString, QString));
void distances(LevenshteinDistance &obj);
QString getString(string message);
void timeTest(LevenshteinDistance &obj);
void getDistance(int (LevenshteinDistance::*func)(QString, QString), LevenshteinDistance &obj);
vector<double> timeTestMethod(int (LevenshteinDistance::*func)(QString, QString), LevenshteinDistance &obj);
QString randomString(int size);
string spacesString(unsigned long len);
void writeVectorToFile(vector<double> vec, ofstream &file);
void memoryTest();

const int MAX_STRING_LEN = 30;
const int TESTS_PER_WORD_LEN = 1;
const int MAX_TEST_WORDLEN = 8;
const int MIN_TEST_WORDLEN = 0;
const int STEP = 1;
const string timesFilename = "../times";

int main(int argc, char * argv[])
{
    setlocale(LC_ALL, "rus");

    LevenshteinDistance obj;
//    int r = obj.levenshteinDistance_m("ab", "ac");
    menu(argc, argv);
    return 0;
}

void menu(int argc, char * argv[])
{
    LevenshteinDistance obj;
    TestDistance testDistance;
    int (LevenshteinDistance::*func)(QString, QString);
    bool run = true;
    while (run)
    {
        cout << "1 - расстояние Левенштейна матрично" << endl
             << "2 - расстояние Левенштейна рекурсивно" << endl
             << "3 - расстояние Дамерау-Левенштейна матрично" << endl
             << "4 - расстояние Дамерау-Левенштейна рекурсивно" << endl
             << "5 - все сразу (1-4)" << endl
             << "6 - временной анализ" << endl
             << "7 - тесты" << endl
             //<< "8 - замеры потребляемой памяти" << endl
             << " > ";
        string saction;
        cin >> saction;
        istringstream iss (saction, istringstream::in);
        int action;
        iss >> action;

        bool printFlag;

        switch (action)
        {
            case 1:
                printFlag = getPrintFlag();
                obj.setPrintMatrixFlag(printFlag);
                func = &LevenshteinDistance::levenshteinDistance_m;
                getDistance(func, obj);
                break;
            case 2:
                func = &LevenshteinDistance::levenshteinDistance_r;
                getDistance(func, obj);
                break;
            case 3:
                printFlag = getPrintFlag();
                obj.setPrintMatrixFlag(printFlag);
                func = &LevenshteinDistance::damerauLevenshteinDistance_m;
                getDistance(func, obj);
                break;
            case 4:
                func = &LevenshteinDistance::damerauLevenshteinDistance_r;
                getDistance(func, obj);
                break;
            case 5:
                distances(obj);
                break;
            case 6:
                timeTest(obj);
                cout << "Результаты замеров записаны в файл" << timesFilename << endl;
                break;
            case 7:
                QTest::qExec(&testDistance, argc, argv);
                break;
            //case 8:
                //memoryTest();
                //break;
            default:
                run = false;
        }
    }
}

void memoryTest()
{
    cout << "Для матричного алгоритма вычисления расстояния Левенштейна: "
         << sizeof (int) * 4 << " * размер_str1 * размер_str2 + память под str1 + память под str2"
         << endl;
    cout << "Для рекурсивного алгоритма вычисления расстояния Левенштейна: "
         << sizeof(int) * 4
         << " + память под str1 + память под str2 + память под копию str1[-1] + память под копию str2[-1]"
         << endl;
}

vector<double> timeTestMethod(int (LevenshteinDistance::*func)(QString, QString), LevenshteinDistance &obj)
{
    srand(time(nullptr));
    vector<double> times;
    for (int i = MIN_TEST_WORDLEN; i < MAX_TEST_WORDLEN; i += STEP)
    {
        QString s1 = randomString(i);
        QString s2 = randomString(i);
        double totalTicks = 0.0;
        clock_t t1, t2;
        for (int j = 0; j < TESTS_PER_WORD_LEN; ++j)
        {
            t1 = clock();
            int d = (obj.*func)(s1, s2);
            t2 = clock();
            totalTicks += (t2 - t1) / static_cast<double>(CLOCKS_PER_SEC);
        }
        totalTicks /= TESTS_PER_WORD_LEN;
        times.push_back(totalTicks);
    }
    return times;
}

void timeTest(LevenshteinDistance &obj)
{
    std::vector<double> levMatrTimes, levRecTimes, damLevMatrTimes, damLevRecTimes;
    int (LevenshteinDistance::*func)(QString, QString);

    func = &LevenshteinDistance::levenshteinDistance_m;
    levMatrTimes = timeTestMethod(func, obj);

    func = &LevenshteinDistance::levenshteinDistance_r;
    levRecTimes = timeTestMethod(func, obj);

    func = &LevenshteinDistance::damerauLevenshteinDistance_m;
    damLevMatrTimes = timeTestMethod(func, obj);

    func = &LevenshteinDistance::damerauLevenshteinDistance_r;
    damLevRecTimes = timeTestMethod(func, obj);

    ofstream fout(timesFilename);
    if (fout.is_open())
    {
        fout << "Word len" << spacesString(30 - string("Word len").size())
             << "Lev(M)" << spacesString(30 - string("Lev(M)").size())
             << "Lev(R)" << spacesString(30 - string("Lev(R)").size())
             << "DamLev(M)" << spacesString(30 - string("DamLev(M)").size())
             << "DamLev(R)" << spacesString(30 - string("DamLev(R)").size())
             << endl;
        for (int i = MIN_TEST_WORDLEN, j; i < MAX_TEST_WORDLEN && j < levMatrTimes.size(); i += STEP, ++j)
        {
            string t1 = to_string(levMatrTimes.at(j));
            string t2 = to_string(levRecTimes.at(j));
            string t3 = to_string(damLevMatrTimes.at(j));
            string t4 = to_string(damLevRecTimes.at(j));
            fout << i << spacesString(30 - to_string(i).size())
                 << t1 << spacesString(30 - t1.size())
                 << t2 << spacesString(30 - t2.size())
                 << t3 << spacesString(30 - t3.size())
                 << t4 << spacesString(30 - t4.size())
                 << endl;
        }

        fout << "\n\n";
        writeVectorToFile(levMatrTimes, fout);
        writeVectorToFile(levRecTimes, fout);
        writeVectorToFile(damLevMatrTimes, fout);
        writeVectorToFile(damLevRecTimes, fout);
    }
    else
    {
        cout << "Невозможно открыть файл: " << timesFilename << endl;
    }
    fout.close();
}

void writeVectorToFile(vector<double> vec, ofstream &file)
{
    int len = vec.size();
    for (int i = 0; i < len; ++i)
    {
        file << vec.at(i);
        if (i != len-1)
            file << ",";
    }
    file << "\n";
}

string spacesString(unsigned long len)
{
    string res = "";
    for (unsigned i = 0; i < len; ++i)
        res += " ";
    return res;
}

QString randomString(int size)
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


void getDistance(int (LevenshteinDistance::*func)(QString, QString), LevenshteinDistance &obj)
{
    QString qs1 = getString("Строка 1: ");
    QString qs2 = getString("Строка 2: ");
    int distance = (obj.*func)(qs1, qs2);
    cout << "Расстояние: " << distance << endl;
}

void distances(LevenshteinDistance &obj)
{
    QString qs1 = getString("Строка 1: ");
    QString qs2 = getString("Строка 2: ");

    bool printMatrix = getPrintFlag();
    obj.setPrintMatrixFlag(printMatrix);

    int d1 = obj.levenshteinDistance_m(qs1, qs2);
    int d2 = obj.levenshteinDistance_r(qs1, qs2);
    int d3 = obj.damerauLevenshteinDistance_m(qs1, qs2);
    int d4 = obj.damerauLevenshteinDistance_r(qs1, qs2);

    cout << "Расстояние Левенштейна (матрично): " << d1 << endl
         << "Расстояние Левенштейна (рекурсивно): " << d2 << endl
         << "Расстояние Дамерау-Левенштейна (матрично): " << d3 << endl
         << "Расстояние Дамерау-Левенштейна (рекурсивно): " << d4 << endl;
}

QString getString(string message)
{
    cout << message;
    string str;
//    while (getline(cin, str) && !str.empty())
//    {
//        cout << str;
//        str.clear();
//    }
    cin.ignore(MAX_STRING_LEN, '\n');
    char buff[MAX_STRING_LEN];
    cin.getline(buff, MAX_STRING_LEN);
    return QString(buff);
}

bool getPrintFlag()
{
    cout << "Печатать матрицу? (y/n)" << " > ";
    string answer;
    cin >> answer;
    if (answer == "y")
        return true;
    return false;
}

unsigned long long getTicks()

{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}
