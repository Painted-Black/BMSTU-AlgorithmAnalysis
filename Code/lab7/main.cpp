#include <QCoreApplication>

#include <iostream>
#include <string>
#include <vector>

#include "testsearch.h"
#include "search.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*TestSearch testSearch;
    QTest::qExec(&testSearch, argc, argv)*/;

    string text = "abbeccacbadbabbad";
    string sub = "abbad";

    vector<size_t> s = preffix(sub);

    int aa = 0;

    int idx = KMP(text, sub);
    cout << idx << endl;

    return 0;
}
