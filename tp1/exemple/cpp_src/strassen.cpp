#include <vector>
#include <ctime>
#include "multiplier.h"
#include "conv.h"
#include <cmath>

using namespace std;

void addMatrices(
    vector<vector<float>> &m1,
    vector<vector<float>> &m2,
    vector<vector<float>> &x,
    int size)
{
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            x[i][j] = m1[i][j] + m2[i][j];
}

void substractMatrices(
    vector<vector<float>> &m1,
    vector<vector<float>> &m2,
    vector<vector<float>> &x,
    int size)
{
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            x[i][j] = m1[i][j] - m2[i][j];
}

void strassenSplit(vector<vector<float>> &source,
                   vector<vector<float>> &x11,
                   vector<vector<float>> &x12,
                   vector<vector<float>> &x21,
                   vector<vector<float>> &x22,
                   int half)
{
    for (size_t i = 0; i < half; i++)
    {
        for (size_t j = 0; j < half; j++)
        {
            x11[i][j] = source[i][j];
            x12[i][j] = source[i][j + half];
            x21[i][j] = source[i + half][j];
            x22[i][j] = source[i + half][j + half];
        }
    }
}

void strassenMerge(
    vector<vector<float>> &c11,
    vector<vector<float>> &c12,
    vector<vector<float>> &c21,
    vector<vector<float>> &c22,
    vector<vector<float>> &target,
    int half)
{
    for (size_t i = 0; i < half; i++)
    {
        for (size_t j = 0; j < half; j++)
        {
            target[i][j] = c11[i][j];
            target[i][j + half] = c12[i][j];
            target[i + half][j] = c21[i][j];
            target[i + half][j + half] = c22[i][j];
        }
    }
}

void ikjalgorithm(vector<vector<float>> &A,
                  vector<vector<float>> &B,
                  vector<vector<float>> &C,
                  int size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t k = 0; k < size; k++)
        {
            for (size_t j = 0; j < size; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void rec(vector<vector<float>> &mat1,
         vector<vector<float>> &mat2,
         uint64_t threshold,
         vector<vector<float>> &result,
         int size)
{
    int n = mat1.size();
    int half = n / 2;

    if (n <= threshold)
    {
        ikjalgorithm(mat1, mat2, result, size);
    }
    else
    {
        vector<float> inside(half);
        vector<vector<float>> a11(half, inside),
            a12(half, inside),
            a21(half, inside),
            a22(half, inside),
            b11(half, inside),
            b12(half, inside),
            b21(half, inside),
            b22(half, inside),
            c11(half, inside),
            c12(half, inside),
            c21(half, inside),
            c22(half, inside),
            m1(half, inside),
            m2(half, inside),
            m3(half, inside),
            m4(half, inside),
            m5(half, inside),
            m6(half, inside),
            m7(half, inside),
            aResult(half, inside),
            bResult(half, inside);

        strassenSplit(mat1, a11, a12, a21, a22, half);
        strassenSplit(mat2, b11, b12, b21, b22, half);

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

        vector<float> targetInside(n);
        vector<vector<float>> target(n, targetInside);
        strassenMerge(c11, c12, c21, c22, result, half);
    }
}

vector<vector<float>> multiplyStrassen(vector<vector<float>> &mat1, vector<vector<float>> &mat2)
{
    int size = mat1.size();
    vector<float> x(size);
    vector<vector<float>> xx(size, x);
    rec(mat1, mat2, 1, xx, size);

    return xx;
}