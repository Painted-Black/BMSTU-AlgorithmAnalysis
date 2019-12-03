#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <limits.h>
#include <vector>

#include "algorithm.h"
#include "adjacencymatrix.h"

class BruteForce : public Algorithm
{
public:
    BruteForce();
    int getMinRoute(AdjacencyMatrix *amatrix);
    vector<int> getMinRouteVec();
private:
    void createAdjacencyList();
    void printVec(vector<int> &vec);
    bool isIn(vector<int> v, int elem);
    void allPaths(int init_node, int fin_node,
                  vector<int> path);

    int lmin = INT_MAX;
    vector<int> minRoute;
    AdjacencyMatrix *mAmatrix;
    vector<vector<int>> mAdjacencyList;
    int mN;
//    vector<vector<int>> paths;
};

#endif // BRUTEFORCE_H
