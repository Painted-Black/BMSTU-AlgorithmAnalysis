#include "adjacencymatrix.h"

AdjacencyMatrix::AdjacencyMatrix(string filename)
{
    int cities = 0;
    ifstream fout(filename);
    if (fout.is_open())
    {
        fout >> cities;
    }
    else
        cout << "Невозможно открыть файл " << filename << endl;

    if (cities <= 0 || cities <= 0)
        throw std::bad_alloc();

    mRows = cities;
    mColumns = cities;

    //mValues = (int* ) calloc(mColumns * mRows, sizeof (int));

    mValues = new int[mColumns * mRows];

    for (int i = 0; i < mRows; ++i)
    {
        for (int j = 0; j < mColumns; ++j)
        {
            mValues[i * mColumns + j] = 0;
        }
    }

    if (fout.is_open())
    {
        int val;
        for (int i = 0; i < mRows; ++i)
        {
            for (int j = 0; j < mColumns; ++j)
            {
                fout >> val;
                mValues[i * mColumns + j] = val;
            }
        }
    }
    else
        cout << "Невозможно открыть файл " << filename << endl;
    fout.close();
}


AdjacencyMatrix::~AdjacencyMatrix()
{
    //free(mValues);
    delete [] mValues;
}

void AdjacencyMatrix::print()
{
    for (int i = 0; i < mRows; ++i)
    {
        for (int j = 0; j < mColumns; ++j)
            cout << mValues[i * mColumns + j] << "\t";
        cout << endl;
    }
}

int AdjacencyMatrix::cities()
{
    return mRows;
}

int AdjacencyMatrix::at(int row, int col) const
{
    if (col < 0 || col >= mColumns || row < 0 || row >= mRows)
        throw std::out_of_range("Matrix index out of range.");
    return mValues[row * mColumns + col];
}

void AdjacencyMatrix::set(int row, int col, int val)
{
    if (col < 0 || col >= mColumns || row < 0 || row >= mRows)
        throw std::out_of_range("Matrix index out of range.");
    mValues[row * mColumns + col] = val;
}

bool AdjacencyMatrix::isEqual(const AdjacencyMatrix &m1)
{
    if (mRows != m1.mRows || mColumns != m1.mColumns)
        return false;

    for (int i = 0; i < mRows; ++i)
        for (int j = 0; j < mColumns; ++j)
            if (this->at(i, j) != m1.at(i, j))
                return false;
    return true;
}

bool AdjacencyMatrix::isEqual(const AdjacencyMatrix &m1, const AdjacencyMatrix &m2)
{
    if (mRows != m1.mRows || mRows != m2.mRows || m1.mRows != m2.mRows ||
        mColumns != m1.mColumns || mColumns != m2.mColumns || m1.mColumns != m2.mColumns)
        return false;
    for (int i = 0; i < mRows; ++i)
        for (int j = 0; j < mColumns; ++j)
            if (this->at(i, j) != m1.at(i, j) || this->at(i, j) != m2.at(i, j) ||
                m1.at(i, j) != m2.at(i, j))
                return false;
    return true;
}
