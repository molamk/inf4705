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
        vector<float> x11Row;
        vector<float> x12Row;
        vector<float> x21Row;
        vector<float> x22Row;
        for (size_t j = 0; j < half; j++)
        {
            x11Row.push_back(source[i][j]);
            x12Row.push_back(source[i][j + half]);
            x21Row.push_back(source[i + half][j]);
            x22Row.push_back(source[i + half][j + half]);
        }
        x11.push_back(x11Row);
        x12.push_back(x12Row);
        x21.push_back(x21Row);
        x22.push_back(x22Row);
    }
}

vector<vector<float>> strassenMerge(
    vector<vector<float>> &c11,
    vector<vector<float>> &c12,
    vector<vector<float>> &c21,
    vector<vector<float>> &c22)
{
    vector<vector<float>> result;

    int half = c11.size();

    for (size_t i = 0; i < half * 2; i++)
    {
        vector<float> row;
        for (size_t j = 0; j < half * 2; j++)
        {
            if (i < half && j < half)
                row.push_back(c11[i][j]);
            else if (i < half && j >= half)
                row.push_back(c12[i][j - half]);
            else if (i >= half && j < half)
                row.push_back(c21[i - half][j]);
            else if (i >= half && j >= half)
                row.push_back(c22[i - half][j - half]);
        }
        result.push_back(row);
    }

    return result;
}

vector<vector<float>> rec(vector<vector<float>> mat1, vector<vector<float>> mat2, uint64_t threshold)
{
    int n = mat1.size();

    if (n <= threshold)
    {
        return multiplyConv(mat1, mat2);
    }
    else
    {
        vector<vector<float>> a11;
        vector<vector<float>> a12;
        vector<vector<float>> a21;
        vector<vector<float>> a22;
        strassenSplit(mat1, a11, a12, a21, a22);

        vector<vector<float>> b11;
        vector<vector<float>> b12;
        vector<vector<float>> b21;
        vector<vector<float>> b22;
        strassenSplit(mat2, b11, b12, b21, b22);

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

        return strassenMerge(c11, c12, c21, c22);
    }
}

vector<vector<float>> multiplyStrassen(vector<vector<float>> &mat1, vector<vector<float>> &mat2)
{
    return rec(mat1, mat2, 1);
}