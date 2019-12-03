#ifndef ANTCOLONY_H
#define ANTCOLONY_H

#include <limits.h>
#include <vector>
#include <math.h>

#include "algorithm.h"
#include "adjacencymatrix.h"
#include "ant.h"

class AntColony : public Algorithm
{
public:
    AntColony();
    int getMinRoute(AdjacencyMatrix *amatrix, size_t alpha, size_t beta, double q, size_t tmax);
    vector<int> getMinRoute();
private:
    int lmin = INT_MAX;
    vector<int> minRoute;
    AdjacencyMatrix *mAmatrix;
    unsigned int mN;

    void getRoute(vector<int> all, int start, vector<int> &route, size_t &len,
                   vector<vector<double>> tao, vector<vector<double>> attraction,
                   size_t alpha, size_t beta);
//    vector<int> getCurRoute(int * curRouteLen, int start, vector<vector<double>> &tao);
    vector<int> deleteFromVector(vector<int> to, int last);
    vector<double> getProbability(int from, vector<int> to, vector<vector<double>> tao, vector<vector<double>> attraction,
                                   size_t alpha, size_t beta);
    bool includes(int a, int b, vector<int> route);
};

#endif // ANTCOLONY_H
