#include <vector>
#include <ctime>
#include "multiplier.h"
#include "conv.h"
#include <cmath>

using namespace std;

vector<vector<float>> addMatrices(
    vector<vector<float>> &m1,
    vector<vector<float>> &m2)
{
    vector<vector<float>> x = m1;

    for (size_t i = 0; i < m1.size(); i++)
        for (size_t j = 0; j < m1.size(); j++)
            x[i][j] += m2[i][j];

    return x;
}

vector<vector<float>> substractMatrices(
    vector<vector<float>> &m1,
    vector<vector<float>> &m2)
{
    vector<vector<float>> x = m1;

    for (size_t i = 0; i < m1.size(); i++)
        for (size_t j = 0; j < m1.size(); j++)
            x[i][j] -= m2[i][j];

    return x;
}

void strassenSplit(vector<vector<float>> &source,
                   vector<vector<float>> &x11,
                   vector<vector<float>> &x12,
                   vector<vector<float>> &x21,
                   vector<vector<float>> &x22)
{
    int half = source.size() / 2;

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
    vector<vector<float>> &target)
{
    int half = c11.size();

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

vector<vector<float>> rec(vector<vector<float>> mat1, vector<vector<float>> mat2, uint64_t threshold)
{
    int n = mat1.size();
    int half = n / 2;

    if (n <= threshold)
    {
        return multiplyConv(mat1, mat2);
    }
    else
    {
        vector<float> inside(half);
        vector<vector<float>> a11(half, inside);
        vector<vector<float>> a12(half, inside);
        vector<vector<float>> a21(half, inside);
        vector<vector<float>> a22(half, inside);
        strassenSplit(mat1, a11, a12, a21, a22);

        vector<vector<float>> b11(half, inside);
        vector<vector<float>> b12(half, inside);
        vector<vector<float>> b21(half, inside);
        vector<vector<float>> b22(half, inside);
        strassenSplit(mat2, b11, b12, b21, b22);

        // vector<vector<float>> aResult(half, inside);
        // vector<vector<float>> bResult(half, inside);

        vector<vector<float>> m1 = rec(addMatrices(a11, a22), addMatrices(b11, b22), threshold);
        vector<vector<float>> m2 = rec(addMatrices(a21, a22), b11, threshold);
        vector<vector<float>> m3 = rec(a11, substractMatrices(b12, b22), threshold);
        vector<vector<float>> m4 = rec(a22, substractMatrices(b21, b11), threshold);
        vector<vector<float>> m5 = rec(addMatrices(a11, a12), b22, threshold);
        vector<vector<float>> m6 = rec(substractMatrices(a21, a11), addMatrices(b11, b12), threshold);
        vector<vector<float>> m7 = rec(substractMatrices(a12, a22), addMatrices(b21, b22), threshold);

        vector<vector<float>> c11_1 = addMatrices(m1, m4);
        vector<vector<float>> c11_2 = addMatrices(c11_1, m7);
        vector<vector<float>> c11 = substractMatrices(c11_2, m5);

        vector<vector<float>> c12 = addMatrices(m3, m5);

        vector<vector<float>> c21 = addMatrices(m2, m4);

        vector<vector<float>> c22_1 = addMatrices(m1, m3);
        vector<vector<float>> c22_2 = addMatrices(c22_1, m6);
        vector<vector<float>> c22 = substractMatrices(c22_2, m2);

        vector<float> targetInside(n);
        vector<vector<float>> target(n, targetInside);
        strassenMerge(c11, c12, c21, c22, target);

        return target;
    }
}

vector<vector<float>> multiplyStrassen(vector<vector<float>> &mat1, vector<vector<float>> &mat2)
{
    return rec(mat1, mat2, 1);
}