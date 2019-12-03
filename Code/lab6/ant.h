#ifndef ANT_H
#define ANT_H

#include <iostream>
#include <vector>

using namespace std;

class Ant
{
public:
    Ant(int startVertice);
    void putInVertice(int v);
private:
    int mCurVertice;
    vector<int> mVisited;
};

#endif // ANT_H
