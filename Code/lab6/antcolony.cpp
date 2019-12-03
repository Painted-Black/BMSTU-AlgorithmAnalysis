#include "antcolony.h"

AntColony::AntColony()
    : Algorithm ()
{

}

void AntColony::getRoute(vector<int> all, int start, vector<int> &route, size_t &len,
               vector<vector<double>> tao, vector<vector<double>> attraction,
               size_t alpha, size_t beta)
{

    route.resize(0);
    route.push_back(start);
    vector<int> to = deleteFromVector(all, start);
    size_t n_1 = tao.size() - 2;
    int from;
    double coin, sum;
    bool flag;

    for (size_t i = 0; i < n_1; i++){
        sum = 0;
        flag = true;
        from = route[i];
        vector<double> p = getProbability(from, to, tao, attraction, alpha, beta);
        coin = double(rand() % 10000) / 10000;
        for (size_t j = 0; j < p.size() && flag; j++){
            sum += p[j];
            if (coin < sum){
                route.push_back(to[j]);
                len += mAmatrix->at(from, to[j]);
                to = deleteFromVector(to, to[j]);
                flag = false;
            }
        }
    }
    len += mAmatrix->at(route[route.size()-1], to[0]);
    route.push_back(to[0]);
    len += mAmatrix->at(route[route.size()-1], route[0]);
    route.push_back(route[0]);
}

int AntColony::getMinRoute(AdjacencyMatrix *amatrix, size_t alpha, size_t beta, double q, size_t tmax)
{
    lmin = INT_MAX;
    minRoute.clear();

    this->mAmatrix = amatrix;
    this->mN = static_cast<unsigned int>(mAmatrix->cities());

    double tao_min, tao_start, Q;
    vector<int> all(mN);
    Q = 350;
    tao_min = 0.001;
    tao_start = 1.0 / mN;
//    tao_start = 0.5;

    vector<vector<int>> routes(mN);
    vector<size_t> lens(mN);

    vector<vector<double>> attraction(mN);
    vector<vector<double>> tao(mN);

    for (size_t i = 0; i < mN; i++)
    {
        attraction[i].resize(mN);
        tao[i].resize(mN);
        lens[i] = 0;
        all[i] = static_cast<int>(i);
        for (size_t j = 0; j < mN; j++)
        {
            if (i != j) {
                attraction[i][j] = 1.0 / mAmatrix->at(i, j);
                tao[i][j] = tao_start;
            }
        }
    }

    for (size_t time = 0; time < tmax; time++){
        for (size_t k = 0; k < mN; k++){
            getRoute(all, static_cast<int>(k), routes[k], lens[k], tao, attraction, alpha, beta);
            if (lens[k] < lmin)
            {
                lmin = lens[k];
                minRoute = routes[k];
             }
        }
        for (size_t i = 0; i < mN; i++)
            for (size_t j = 0; j < mN; j++)
            {
                double sum = 0;
                for (size_t m = 0; m < mN; m++)
                {
                    if (includes(static_cast<int>(i), static_cast<int>(j), routes[m]))
                        sum += Q/lens[m];
                }

                tao[i][j] = tao[i][j]*(1 - q) + sum;
                if (tao[i][j] < tao_min)
                     tao[i][j] = tao_min;
            }
    }
    return lmin;
}

vector<int> AntColony::getMinRoute()
{
    return minRoute;
}

bool AntColony::includes(int a, int b, vector<int> route)
{
    bool res = false;
    size_t m = route.size()-1;
    for (size_t i = 0; i < m; i++){
        if (a == route[i] && b == route[i+1])
            res = true;
    }
    return res;
}

vector<int> AntColony::deleteFromVector(vector<int> to, int last)
{
    size_t n = to.size();
    vector<int> cur;
    for (size_t i = 0; i < n; i++)
        if (to[i] != last)
            cur.push_back(to[i]);
    return cur;
}

vector<double> AntColony::getProbability(int from, vector<int> to,
                                         vector<vector<double>> tao, vector<vector<double>> attraction,
                                         size_t alpha, size_t beta)
{

    double znam = 0, chisl = 0;
    size_t n = to.size();
    vector<double> result(n);
    for (size_t i = 0; i < n; i++){
        znam += pow(tao[from][to[i]], alpha) * pow(attraction[from][to[i]], beta);
    }
    for (size_t j = 0; j < n; j++) {
        chisl = pow(tao[from][to[j]], alpha) * pow(attraction[from][to[j]], beta);
        result[j] = chisl / znam;
    }
    return result;
}

//vector<int> AntColony::getCurRoute(int * curRouteLen, int start, vector<vector<double> > &tao)
//{
//    int len = 0;
//    vector <int> route;
//    route.push_back(start);

//    double coin, sum;
//    bool flag;
//    int from;
//    size_t n_1 = tao.size() - 2;

//    for (size_t i = 0; i < n_1; i++)
//    {
//        sum = 0;
//        flag = true;
//        from = route[i];
//        vector<double> p = getProbability(from, to, tao, attraction, alpha, beta);
//        coin = double(rand() % 10000) / 10000;
////        for (size_t j = 0; j < p.size() && flag; j++)
//        {
////            sum += p[j];
//            if (coin < sum)
//            {
////                route.push_back(to[j]);
////                len += d[from][to[j]];
////                to = new_vec_without_last(to, to[j]);
////                flag = false;
//            }
//        }
//    }
//}

//int AntColony::getMinRoute(AdjacencyMatrix *amatrix, size_t alpha, size_t beta, double q, size_t tmax)
//{
//    // q - коэффицент испарения

//    this->mAmatrix = amatrix;
//    this->mN = static_cast<unsigned int>(mAmatrix->cities());

//    lmin = INT_MAX;
//    minRoute.clear();

//    double tao_min, tao_start, Q;
//    vector<size_t> all(mN);
//    Q = 350;
//    tao_min = 0.001;
//    tao_start = 1 / mN;
//    //tao_start = 0.5;

//    vector<vector<double>> tao(mN);
//    vector<Ant> ants;

//    for (size_t i = 0; i < mN; i++)
//    {
//        tao[i].resize(mN);
//        all[i] = i;
//        for (size_t j = 0; j < mN; j++) {
//            if (i != j)
//            {
//                tao[i][j] = tao_start;
//            }
//        }
//    }

//    for (size_t t = 0; t < tmax; ++t)
//    {
//        for (int v = 0; v < mN; ++v)
//            ants.push_back(Ant(v));
//        for (int k = 0; k < mN; ++k)
//        {

//        }
//    }
//    int a = 0;

    //    return lmin;
//}
