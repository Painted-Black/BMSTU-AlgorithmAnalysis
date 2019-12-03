#include "ant.h"

Ant::Ant()
{

}

void Ant::putInVertice(int v)
{
    mCurVertice = v;
    mVisited.push_back(mCurVertice);
}
