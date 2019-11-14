#include "mymatrix.h"

MyMatrix::MyMatrix(int rows, int cols, bool randomize, int defaultValue)
{
    if (cols < 0 || rows < 0)
        throw std::bad_alloc();

    mColumns = cols;
    mRows = rows;

    mValues = new int[mColumns * mRows];
    for (int i = 0; i < mRows; ++i)
        for (int j = 0; j < mColumns; ++j)
        {
            if (randomize)
            {
                mValues[i * mColumns + j] = mMinRand + rand() % mRandRange;
            }
            else
                mValues[i * mColumns + j] = defaultValue;
        }
}

MyMatrix::MyMatrix(const MyMatrix &m)
{
    mRows = m.mRows;
    mColumns = m.mColumns;
    mValues = new int[mColumns * mRows];

    for (int i = 0; i < mRows; ++i)
        for (int j = 0; j < mColumns; ++j)
            mValues[i * mColumns + j] = m.at(i, j);
}

MyMatrix::MyMatrix(std::vector<std::vector<int>> &vec)
{
    mRows = static_cast<int>(vec.size());
    mColumns = static_cast<int>(vec.at(0).size());

    mValues = new int[mRows * mColumns];

    for (int i = 0; i < mRows; ++i)
        for (int j = 0; j < mColumns; ++j)
        {
            mValues[i * mColumns + j] = vec.at(i).at(j);
        }
}

MyMatrix::MyMatrix(std::initializer_list<std::initializer_list<int> > list)
{
    mRows = static_cast<int>(list.size());
    mColumns = static_cast<int>(list.begin()->size());

    mValues = new int[mRows * mColumns];

    int i = 0, j = 0;
    for(auto& item : list)
    {
        for (auto& jtem : item)
        {
            mValues[i * mColumns + j] = jtem;
            ++j;
        }
        j = 0;
        ++i;
    }
}

MyMatrix::~MyMatrix()
{
    delete [] mValues;
}

void MyMatrix::print()
{
    for (int i = 0; i < mRows; ++i)
    {
        for (int j = 0; j < mColumns; ++j)
        {
            std::cout << mValues[i * mColumns + j] << "\t";
        }
        std::cout << std::endl;
    }
}

int MyMatrix::at(int row, int col) const
{
    if (col < 0 || col >= mColumns || row < 0 || row >= mRows)
        throw std::out_of_range("Matrix index out of range.");
    return mValues[row * mColumns + col];
}

void MyMatrix::set(int row, int col, int val)
{
    if (col < 0 || col >= mColumns || row < 0 || row >= mRows)
        throw std::out_of_range("Matrix index out of range.");
    mValues[row * mColumns + col] = val;
}

MyMatrix MyMatrix::multiply(const MyMatrix &m)
{
    if (mColumns != m.mRows)
        throw std::logic_error("Attempt to multiply matrices of different dimensions.");

    MyMatrix result(mRows, m.mColumns, 0);

    for (int i = 0; i < mRows; ++i)
        for (int j = 0; j < m.mColumns; ++j)
            for (int k = 0; k < mColumns; ++k)
            {
                int resNum = result.at(i, j) + this->at(i, k) * m.at(k, j);
                result.set(i, j, resNum);
            }
    return result;
}

MyMatrix MyMatrix::multiplyVinograd(const MyMatrix &m)
{
    if (mColumns != m.mRows)
        throw std::logic_error("Attempt to multiply matrices of different dimensions.");

    MyMatrix result(mRows, m.mColumns, 0);

    int* mulH = new int[result.mRows];
    int* mulV = new int[result.mColumns];

    for (int i = 0; i < result.mRows; ++i)
        mulH[i] = 0;
    for (int i = 0; i < result.mColumns; ++i)
        mulV[i] = 0;

    for (int i = 0; i < result.mRows; ++i)
        for (int j = 0; j < m.mRows / 2; ++j)
            mulH[i] += this->at(i, j * 2) * this->at(i, j * 2 + 1);

    for (int i = 0; i < result.mColumns; ++i)
        for (int j = 0; j < m.mRows / 2; ++j)
            mulV[i] += m.at(2 * j, i) * m.at(j * 2 + 1, i);

    for (int i = 0; i < result.mRows; ++i)
        for (int j = 0; j < result.mColumns; ++j)
        {
            result.set(i, j, - mulH[i] - mulV[j]);
            for (int k = 0; k < m.mRows / 2; ++k)
            {
                int newRes = result.at(i, j) +
                             (this->at(i, 2 * k) + m.at(2 * k + 1, j)) *
                             (this->at(i, 2 * k + 1) + m.at(2 * k, j));
                result.set(i, j, newRes);
            }
        }

    if (mColumns % 2)
    {
        for (int i = 0; i < mRows; ++i)
            for (int j = 0; j < m.mColumns; ++j)
            {
                int newRes = result.at(i, j) +
                             this->at(i, mColumns - 1) *
                             m.at(mColumns - 1, j);
                result.set(i, j, newRes);
            }
    }
    delete [] mulH;
    delete [] mulV;
    return result;
}

MyMatrix MyMatrix::multiplyVinogradOptimized(const MyMatrix &m)
{
    if (mColumns != m.mRows)
        throw std::logic_error("Attempt to multiply matrices of different dimensions.");

    MyMatrix result(mRows, m.mColumns, 0);

    int* mulH = new int[result.mRows];
    int* mulV = new int[result.mColumns];

    for (int i = 0; i < result.mRows; ++i)
        mulH[i] = 0;
    for (int i = 0; i < result.mColumns; ++i)
        mulV[i] = 0;

    int cols1Mod2 = mColumns % 2;
    //int rows2Mod2 = m.mRows % 2;

    for (int i = 0; i < mRows; ++i)
        for (int j = 0; j < (mColumns - cols1Mod2); j += 2)
            mulH[i] += this->at(i, j) * this->at(i, j + 1);

    for (int i = 0; i < m.mColumns; ++i)
        for (int j = 0; j < (m.mRows - cols1Mod2); j += 2)
            mulV[i] += m.at(j, i) * m.at(j + 1, i);

    for (int i = 0; i < mRows; ++i)
        for (int j = 0; j < m.mColumns; ++j)
        {
            int buff = -(mulH[i] + mulV[j]);
            for (int k = 0; k < (mColumns - cols1Mod2); k += 2)
                buff += (this->at(i, k + 1) + m.at(k, j)) *
                        (this->at(i, k) + m.at(k + 1, j));
            result.set(i, j, buff);
        }

    if (cols1Mod2)
    {
        for (int i = 0; i < result.mRows; ++i)
            for (int j = 0; j < result.mColumns; ++j)
            {
                int newRes = result.at(i, j) +
                             this->at(i, mColumns - 1) *
                             m.at(mColumns - 1, j);
                result.set(i, j, newRes);
            }
    }
    delete [] mulH;
    delete [] mulV;
    return result;
}

bool MyMatrix::isEqual(const MyMatrix &m1)
{
    if (mRows != m1.mRows || mColumns != m1.mColumns)
        return false;

    for (int i = 0; i < mRows; ++i)
        for (int j = 0; j < mColumns; ++j)
            if (this->at(i, j) != m1.at(i, j))
                return false;
    return true;
}

bool MyMatrix::isEqual(const MyMatrix &m1, const MyMatrix &m2)
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

