#include "bruteforce.h"

BruteForce::BruteForce()
    : Algorithm ()
{

}


int BruteForce::getMinRoute(AdjacencyMatrix *amatrix)
{
    if (amatrix->cities() > 15)
        throw logic_error("Поиск займет слишком много времени!\n");

    this->mAmatrix = amatrix;
    this->mN = mAmatrix->cities();
    minRoute.clear();
    mAdjacencyList.clear();
    lmin = INT_MAX;

    createAdjacencyList();

    for (int i = 0; i < mN; ++i)
        for (int j = 0; j < mN; ++j)
        {
            if (i != j)
            {
                vector<int> b;
                allPaths(i, j, b);
            }
        }

//    printVec(minRoute);
//    cout << lmin << endl;

    return lmin;
}

void BruteForce::createAdjacencyList()
{
    for (int i = 0; i < mN; ++i)
    {
        vector<int> oneNodeList;
        oneNodeList.push_back(i);

        for (int j = 0; j < mN; ++j)
        {
            if (i != j)
                oneNodeList.push_back(j);
        }

        mAdjacencyList.push_back(oneNodeList);
    }
}

void BruteForce::allPaths(int init_node, int fin_node, vector<int>path)
{
    path.push_back(init_node); // добавляем в путь текущую ноду

    if (init_node == fin_node)
    {
        //путь найден, печатаем и возвращаемся.
        if (path.size() == mAdjacencyList.size())
        {
            int l = 0, n = static_cast<int>(path.size()), i;
            for (i = 0; i < n - 1; ++i)
            {
                l += mAmatrix->at(path.at(i), path.at(i + 1));
            }
            l += mAmatrix->at(path.at(i), path.at(0));
            if (l < lmin)
            {
                lmin = l;
                minRoute = path;
            }
        }
        return;
    }

    if (mAdjacencyList[init_node].empty())
        return; // Путь не найден

    //рекурсивно продолжаем поиск для дочерних нод
    for (auto subnode:mAdjacencyList[init_node])
    {
        if (!isIn(path, subnode))
            allPaths(subnode, fin_node, path);
    }
    return;
}

vector<int> BruteForce::getMinRouteVec()
{
    return minRoute;
}

void BruteForce::printVec(vector<int> &vec)
{
    for (unsigned int i = 0; i < vec.size(); ++i)
    {
        cout << vec.at(i) << "\t";
    }
    cout << endl;
}

bool BruteForce::isIn(vector<int>v, int elem)
{
    for (unsigned int i = 0; i < v.size(); ++i)
        if (v.at(i) == elem)
            return true;
    return false;
}
