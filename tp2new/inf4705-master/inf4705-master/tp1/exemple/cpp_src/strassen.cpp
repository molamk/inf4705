#include <vector>
#include <ctime>
#include "multiplier.h"
#include "conv.h"
#include <cmath>

using namespace std;

void addMatrices(
    vector<int> &m1,
    vector<int> &m2,
    vector<int> &x,
    int size)
{
    for (size_t i = 0; i < m1.size(); i++)
        x[i] = m1[i] + m2[i];
}

void substractMatrices(
    vector<int> &m1,
    vector<int> &m2,
    vector<int> &x,
    int size)
{
    for (size_t i = 0; i < m1.size(); i++)
        x[i] = m1[i] - m2[i];
}

void strassenSplit(vector<int> &source,
                   vector<int> &x11,
                   vector<int> &x12,
                   vector<int> &x21,
                   vector<int> &x22,
                   int size)
{
    int rowSize = (int)sqrt(size * 2);
    for (size_t i = 0; i < rowSize / 2; i++)
        for (size_t j = 0; j < rowSize / 2; j++)
        {
            int idx = (i * rowSize) / 2 + j;
            x11[idx] = source[i * rowSize + j];
            x12[idx] = source[i * rowSize + j + rowSize / 2];
            x21[idx] = source[(i + rowSize / 2) * rowSize + j];
            x22[idx] = source[(i + rowSize / 2) * rowSize + j + rowSize / 2];
        }
}

void strassenMerge(
    vector<int> &c11,
    vector<int> &c12,
    vector<int> &c21,
    vector<int> &c22,
    vector<int> &target,
    int size)
{
    int rowSize = (int)sqrt(size);
    for (size_t i = 0; i < rowSize; i++)
        for (size_t j = 0; j < rowSize; j++)
        {
            int idx = (i * rowSize) + j;
            target[i * rowSize * 2 + j] = c11[idx];
            target[i * rowSize * 2 + j + rowSize] = c12[idx];
            target[(i + rowSize) * rowSize * 2 + j] = c21[idx];
            target[(i + rowSize) * rowSize * 2 + j + rowSize] = c22[idx];
        }
}

void ikjalgorithm(vector<int> &mat1, vector<int> &mat2, vector<int> &result, int size)
{
    int rowSize = (int)sqrt(size);

    for (size_t i = 0; i < rowSize; i++)
    {
        for (size_t j = 0; j < rowSize; j++)
        {
            int curr = 0;
            for (size_t k = 0; k < rowSize; k++)
            {
                curr += mat1[i * rowSize + k] * mat2[k * rowSize + j];
            }
            result[i * rowSize + j] = curr;
        }
    }
}

void rec(vector<int> &mat1,
         vector<int> &mat2,
         uint64_t threshold,
         vector<int> &result,
         int size)
{
    int n = size;
    int half = n / 4;

    if (n <= threshold)
    {
        ikjalgorithm(mat1, mat2, result, size);
    }
    else
    {
        vector<int> a11(half);
        vector<int> a12(half);
        vector<int> a21(half);
        vector<int> a22(half);
        vector<int> b11(half);
        vector<int> b12(half);
        vector<int> b21(half);
        vector<int> b22(half);
        vector<int> c11(half);
        vector<int> c12(half);
        vector<int> c21(half);
        vector<int> c22(half);
        vector<int> m1(half);
        vector<int> m2(half);
        vector<int> m3(half);
        vector<int> m4(half);
        vector<int> m5(half);
        vector<int> m6(half);
        vector<int> m7(half);
        vector<int> aResult(half);
        vector<int> bResult(half);

        strassenSplit(mat1, a11, a12, a21, a22, half * 2);
        strassenSplit(mat2, b11, b12, b21, b22, half * 2);

        addMatrices(a11, a22, aResult, half);
        addMatrices(b11, b22, bResult, half);
        rec(aResult, bResult, threshold, m1, half);

        addMatrices(a21, a22, aResult, half);
        rec(aResult, b11, threshold, m2, half);

        substractMatrices(b12, b22, bResult, half);
        rec(a11, bResult, threshold, m3, half);

        substractMatrices(b21, b11, bResult, half);
        rec(a22, bResult, threshold, m4, half);

        addMatrices(a11, a12, aResult, half);
        rec(aResult, b22, threshold, m5, half);

        substractMatrices(a21, a11, aResult, half);
        addMatrices(b11, b12, bResult, half);
        rec(aResult, bResult, threshold, m6, half);

        substractMatrices(a12, a22, aResult, half);
        addMatrices(b21, b22, bResult, half);
        rec(aResult, bResult, threshold, m7, half);

        addMatrices(m3, m5, c12, half);
        addMatrices(m2, m4, c21, half);

        addMatrices(m1, m4, aResult, half);
        addMatrices(aResult, m7, bResult, half);
        substractMatrices(bResult, m5, c11, half);

        addMatrices(m1, m3, aResult, half);
        addMatrices(aResult, m6, bResult, half);
        substractMatrices(bResult, m2, c22, half);

        strassenMerge(c11, c12, c21, c22, result, half);
    }
}

vector<int> multiplyStrassen(vector<int> &mat1, vector<int> &mat2)
{
    int size = mat1.size();
    vector<int> result(size);
    uint64_t threshold = 1;

    rec(mat1, mat2, threshold, result, size);

    return result;
}