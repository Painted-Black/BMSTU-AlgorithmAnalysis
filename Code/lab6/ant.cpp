#include "ant.h"

Ant::Ant(int startVertice)
{
    mCurVertice = startVertice;
    mVisited.push_back(mCurVertice);
}

void Ant::putInVertice(int v)
{
    mCurVertice = v;
    mVisited.push_back(mCurVertice);
}
