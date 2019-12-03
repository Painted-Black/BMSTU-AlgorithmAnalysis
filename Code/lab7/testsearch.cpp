#include "testsearch.h"

TestSearch::TestSearch(QObject *parent) : QObject(parent)
{
    texts.push_back("there they are");
    texts.push_back("there they are");
    texts.push_back("there they are");
    texts.push_back("there they are");
    texts.push_back("there they are");
    texts.push_back("");
    texts.push_back("");
    texts.push_back("abc");
    texts.push_back("there they are");
    texts.push_back("there they are");
    texts.push_back("there they are");

    substrings.push_back("they");
    substrings.push_back("there");
    substrings.push_back("are");
    substrings.push_back("hh");
    substrings.push_back("there they are");
    substrings.push_back("dsd");
    substrings.push_back("");
    substrings.push_back("");
    substrings.push_back("tt");
    substrings.push_back("ee");
    substrings.push_back("aa");

    indices.push_back(6);
    indices.push_back(0);
    indices.push_back(11);
    indices.push_back(-1);
    indices.push_back(0);
    indices.push_back(-1);
    indices.push_back(0);
    indices.push_back(-1);
    indices.push_back(-1);
    indices.push_back(-1);
    indices.push_back(-1);
}

void TestSearch::testKMP()
{
    for (unsigned int i = 0; i < texts.size(); ++i)
    {
        int res = BM(texts.at(i), substrings.at(i));
//        cout << "res: " << res << " trueRes: " << indices.at(i) << endl;
        QVERIFY(res == indices.at(i));
    }
}
