#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

using namespace std;

class AdjacencyMatrix
{
public:
    AdjacencyMatrix(string filename);
    AdjacencyMatrix(int cities, double defaultVal);
    ~AdjacencyMatrix();

    void print();
    int cities();
    int at(int row, int col) const;
    void set(int row, int col, int val);
    bool isEqual(const AdjacencyMatrix& m1);
    bool isEqual(const AdjacencyMatrix& m1, const AdjacencyMatrix& m2);

private:
    int mColumns;
    int mRows;
    int *mValues;
};

#endif // ADJACENCYMATRIX_H
