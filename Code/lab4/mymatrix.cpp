#include <memory>

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

    for (int i = 0; i <mRows; ++i)
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

void MyMatrix::print() const
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

MyMatrix MyMatrix::multiplyVinograd(const MyMatrix &m)
{
    if (mColumns != m.mRows)
        throw std::logic_error("Attempt to multiply matrices of different dimensions.");

    MyMatrix result(mRows, m.mColumns, 0);

    if (result.mColumns == 0 && result.mRows == 0)
        return result;

    int* mulH = new int[result.mRows]{0};
    int* mulV = new int[result.mColumns]{0};

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

MyMatrix MyMatrix::multiplyVinograd_multithread(const MyMatrix &m, int threadsNumber)
{
    if (threadsNumber < 0)
        throw std::logic_error("Threads number is under zero.");

    if (mColumns != m.mRows)
        throw std::logic_error("Attempt to multiply matrices of different dimensions.");

    MyMatrix result(mRows, m.mColumns, 0);

    if (result.mColumns == 0 && result.mRows == 0)
        return result;

    int* mulH = new int[result.mRows]{0};
    int* mulV = new int[result.mColumns]{0};

    for (int i = 0; i < result.mRows; ++i)
        for (int j = 0; j < m.mRows / 2; ++j)
            mulH[i] += this->at(i, j * 2) * this->at(i, j * 2 + 1);

    for (int i = 0; i < result.mColumns; ++i)
        for (int j = 0; j < m.mRows / 2; ++j)
            mulV[i] += m.at(2 * j, i) * m.at(j * 2 + 1, i);

    std::vector<std::thread> threads;
    threadsNumber = qMin(threadsNumber, this->mRows);
    int mtr_num = this->mRows / threadsNumber;
    int reserv_mtr_num = this->mRows % threadsNumber;
    int from_i = 0, to_i;
    for (int i = 0; i < threadsNumber; ++i)
    {
        bool isInc = (reserv_mtr_num--) > 0;
        int appendValue = isInc ? 1 : 0;
        to_i = from_i + mtr_num + appendValue;
        threads.push_back(std::thread(&MyMatrix::threadMultiply, this, std::ref(*this),
                                      std::ref(m), std::ref(result), mulH, mulV,
                                      from_i, to_i));
        from_i = to_i;
    }

    for (int i = 0; i <  threadsNumber; ++i)
    {
        if (threads.at(i).joinable())
            threads.at(i).join();
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

void MyMatrix::threadMultiply(const MyMatrix &m1, const MyMatrix& m2, MyMatrix& res,
                              int* mulH, int* mulV, int from_i, int to_i)
{
    for (int i = from_i; i < to_i; ++i)
        for (int j = 0; j < m2.mColumns; ++j)
        {
            res.set(i, j, - mulH[i] - mulV[j]);
            for (int k = 0; k < m2.mRows / 2; ++k)
            {
                int newRes = res.at(i, j) +
                             (m1.at(i, 2 * k) + m2.at(2 * k + 1, j)) *
                             (m1.at(i, 2 * k + 1) + m2.at(2 * k, j));
                res.set(i, j, newRes);
            }
        }

    if (m1.mColumns % 2 == 1)
    {
        for (int i = from_i; i < to_i; ++i)
            for (int j = 0; j < m2.mColumns; ++j)
            {
                int newRes = res.at(i, j) +
                             m1.at(i, m1.mColumns - 1) *
                             m2.at(m1.mColumns - 1, j);
                res.set(i, j, newRes);
            }
    }
}
