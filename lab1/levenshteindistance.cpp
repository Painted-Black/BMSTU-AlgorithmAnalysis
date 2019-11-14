#include "levenshteindistance.h"

int LevenshteinDistance::levenshteinDistance_m(QString s1, QString s2)
{
    int l1 = s1.size() + 1;
    int l2 = s2.size() + 1;

    int * matrix = (int*) calloc(l1 * l2, sizeof (int));

    for (int i = 0; i < l1; ++i)
    {
        for (int j = 0; j < l2; ++j)
        {
            matrix[i*l2 + j] = 0;
        }
    }

    for (int i = 1; i < l2; ++i)
        matrix[i] = i;
    for (int i = 1; i < l1; ++i)
        matrix[i*l2] = i;

    for (int i = 1; i < l1; ++i)
    {
        for (int j = 1; j < l2; ++j)
        {
            int r1 = matrix[(i - 1)*l2 + j] + 1; // клетка сверху
            int r2 = matrix[i*l2 + (j - 1)] + 1; // клетка слева

            int fine = 1;
            if (s1.at(i - 1) == s2.at(j - 1))
            {
                fine = 0;
            }
            int r3 = matrix[(i - 1)*l2 + (j - 1)] + fine;
            matrix[i*l2 + j] = myMin(r1, r2, r3);
        }
    }
    if (printMatrixFlag)
    {
        cout << "Матрица: " << endl;
        printMatrix(matrix, l1, l2);
    }
    int d = matrix[(l1 - 1)*l2 + (l2 - 1)];
    free(matrix);
    return d;
}

void LevenshteinDistance::printMatrix(int *m, int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << m[i*cols + j] << "\t";
        }
        cout << endl;
    }
}

int LevenshteinDistance::myMin(int v1, int v2, int v3)
{
    return min(v3, min(v1, v2));
}

int LevenshteinDistance::levenshteinDistance_r(QString s1, QString s2)
{
    if (s1.size() == 0 && s2.size() == 0)
        return 0;
    if (s1.size() == 0)
        return s2.size();
    if (s2.size() == 0)
        return s1.size();

    QString newS1 = s1.left(s1.size() - 1);
    QString newS2 = s2.left(s2.size() - 1);
    int r1 = levenshteinDistance_r(newS1, s2) + 1;
    int r2 = levenshteinDistance_r(s1, newS2) + 1;
    int r3 = levenshteinDistance_r(newS1, newS2);
    if (s1.at(s1.size() - 1) != s2.at(s2.size() - 1))
        r3 += 1;
    int distance = myMin(r1, r2, r3);
    return distance;
}

int LevenshteinDistance::damerauLevenshteinDistance_m(QString s1, QString s2)
{
    int l1 = s1.size() + 1;
    int l2 = s2.size() + 1;

    int * matrix = (int*) calloc(l1 * l2, sizeof (int));

    for (int i = 0; i < l1; ++i)
    {
        for (int j = 0; j < l2; ++j)
        {
            matrix[i*l2 + j] = 0;
        }
    }

    for (int i = 1; i < l2; ++i)
        matrix[i] = i;
    for (int i = 1; i < l1; ++i)
        matrix[i*l2] = i;

    for (int i = 1; i < l1; ++i)
    {
        for (int j = 1; j < l2; ++j)
        {
            int r1 = matrix[(i - 1)*l2 + j] + 1; // клетка сверху
            int r2 = matrix[i*l2 + (j - 1)] + 1; // клетка слева

            int fine = 1;
            if (s1.at(i - 1) == s2.at(j - 1))
            {
                fine = 0;
            }
            int r3 = matrix[(i - 1)*l2 + (j - 1)] + fine;
            int distance = myMin(r1, r2, r3);

            if (i > 1 && j > 1)
            {
                if (s1.at(i-1) == s2.at(j-2) && s2.at(j-1) == s1.at(i-2))
                    distance = min(distance, matrix[(i-2)*l2 + (j-2)] + 1);
            }
            matrix[i*l2 + j] = distance;
        }
    }
    if (printMatrixFlag)
    {
        cout << "Матрица: " << endl;
        printMatrix(matrix, l1, l2);
    }
    int d = matrix[(l1 - 1)*l2 + (l2 - 1)];
    free(matrix);
    return d;
}

int LevenshteinDistance::damerauLevenshteinDistance_r(QString s1, QString s2)
{
    int l1 = s1.size();
    int l2 = s2.size();

    if (l1 == 0 && l2 == 0)
        return 0;
    if (l1 == 0)
        return l2;
    if (l2 == 0)
        return l1;

    QString newS1 = s1.left(l1 - 1);
    QString newS2 = s2.left(l2 - 1);
    int r1 = levenshteinDistance_r(newS1, s2) + 1;
    int r2 = levenshteinDistance_r(s1, newS2) + 1;
    int r3 = levenshteinDistance_r(newS1, newS2);
    if (s1.at(l1 - 1) != s2.at(l2 - 1))
        r3 += 1;
    int distance = myMin(r1, r2, r3);

    if (l1 >= 2 && l2 >= 2 && s1.at(l1 - 1) == s2.at(l2 - 2) &&
            s1.at(l1 - 2) == s2.at(l2 - 1))
    {
        newS1 = s1.left(l1 - 2);
        newS2 = s2.left(l2 - 2);
        distance = min(distance, damerauLevenshteinDistance_r(newS1, newS2) + 1);
    }

    return distance;
}

void LevenshteinDistance::setPrintMatrixFlag(bool value)
{
    printMatrixFlag = value;
}
