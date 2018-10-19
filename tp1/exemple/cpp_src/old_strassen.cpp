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
    // // cout << "add\tsize = " << size << endl;
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
    // // cout << "sub\tsize = " << size << endl;
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            x[i][j] = m1[i][j] - m2[i][j];
}

void strassenSplit(const vector<vector<float>> &source,
                   vector<vector<float>> &x11,
                   vector<vector<float>> &x12,
                   vector<vector<float>> &x21,
                   vector<vector<float>> &x22,
                   int half)
{
    // // cout << "strassenSplit\thalf = " << half << endl;
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
    // // cout << "merge\tsize = " << half << endl;
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

void ikjalgorithm(const vector<vector<float>> &A,
                  const vector<vector<float>> &B,
                  vector<vector<float>> &C,
                  int size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            float curr = 0;
            for (size_t k = 0; k < size; k++)
            {
                curr += A[i][k] * B[k][j];
            }
            C[i][j] = curr;
        }
    }
}

void initRows(vector<float> &rows, int size)
{
    vector<float> x(size);
    rows.swap(x);
}

void initMatrx(vector<vector<float>> &m, vector<vector<float>> &r)
{
    vector<vector<float>> x(r);
    m.swap(x);
}

class Strassen
{
  public:
    Strassen(int threshold, vector<vector<float>> &mat1)
    {
        _threshold = threshold;
        // int half = _size / 2;

        // vector<float> r;
        // initRows(r, size);

        initMatrx(a11, mat1);
        initMatrx(a12, mat1);
        initMatrx(a21, mat1);
        initMatrx(a22, mat1);
        initMatrx(b11, mat1);
        initMatrx(b12, mat1);
        initMatrx(b21, mat1);
        initMatrx(b22, mat1);
        initMatrx(c11, mat1);
        initMatrx(c12, mat1);
        initMatrx(c21, mat1);
        initMatrx(c22, mat1);
        initMatrx(m1, mat1);
        initMatrx(m2, mat1);
        initMatrx(m3, mat1);
        initMatrx(m4, mat1);
        initMatrx(m5, mat1);
        initMatrx(m6, mat1);
        initMatrx(m7, mat1);
        initMatrx(aResult, mat1);
        initMatrx(bResult, mat1);
    }

    void fancyRec(const vector<vector<float>> &mat1,
                  const vector<vector<float>> &mat2,
                  vector<vector<float>> &result,
                  int size)
    {
        int n = size;
        int half = size / 2;

        if (n <= _threshold)
            ikjalgorithm(mat1, mat2, result, n);
        else
        {
            strassenSplit(mat1, a11, a12, a21, a22, half);
            strassenSplit(mat2, b11, b12, b21, b22, half);

            addMatrices(a11, a22, aResult, half);
            addMatrices(b11, b22, bResult, half);
            fancyRec(aResult, bResult, m1, half);

            addMatrices(a21, a22, aResult, half);
            fancyRec(aResult, b11, m2, half);

            substractMatrices(b12, b22, bResult, half);
            fancyRec(a11, bResult, m3, half);

            substractMatrices(b21, b11, bResult, half);
            fancyRec(a22, bResult, m4, half);

            addMatrices(a11, a12, aResult, half);
            fancyRec(aResult, b22, m5, half);

            substractMatrices(a21, a11, aResult, half);
            addMatrices(b11, b12, bResult, half);
            fancyRec(aResult, bResult, m6, half);

            substractMatrices(a12, a22, aResult, half);
            addMatrices(b21, b22, bResult, half);
            fancyRec(aResult, bResult, m7, half);

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

  private:
    int _threshold;
    vector<vector<float>> a11;
    vector<vector<float>> a12;
    vector<vector<float>> a21;
    vector<vector<float>> a22;
    vector<vector<float>> b11;
    vector<vector<float>> b12;
    vector<vector<float>> b21;
    vector<vector<float>> b22;
    vector<vector<float>> c11;
    vector<vector<float>> c12;
    vector<vector<float>> c21;
    vector<vector<float>> c22;
    vector<vector<float>> m1;
    vector<vector<float>> m2;
    vector<vector<float>> m3;
    vector<vector<float>> m4;
    vector<vector<float>> m5;
    vector<vector<float>> m6;
    vector<vector<float>> m7;
    vector<vector<float>> aResult;
    vector<vector<float>> bResult;
};

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
        vector<vector<float>> a11,
            a12,
            a21,
            a22,
            b11,
            b12,
            b21,
            b22,
            c11,
            c12,
            c21,
            c22,
            m1,
            m2,
            m3,
            m4,
            m5,
            m6,
            m7,
            aResult,
            bResult;

        initMatrx(a11, mat1);
        initMatrx(a12, mat1);
        initMatrx(a21, mat1);
        initMatrx(a22, mat1);
        initMatrx(b11, mat1);
        initMatrx(b12, mat1);
        initMatrx(b21, mat1);
        initMatrx(b22, mat1);
        initMatrx(c11, mat1);
        initMatrx(c12, mat1);
        initMatrx(c21, mat1);
        initMatrx(c22, mat1);
        initMatrx(m1, mat1);
        initMatrx(m2, mat1);
        initMatrx(m3, mat1);
        initMatrx(m4, mat1);
        initMatrx(m5, mat1);
        initMatrx(m6, mat1);
        initMatrx(m7, mat1);
        initMatrx(aResult, mat1);
        initMatrx(bResult, mat1);

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

    Strassen s(1, mat1);

    int size = mat1.size();
    vector<float> x(size);
    vector<vector<float>> xx(size, x);

    s.fancyRec(mat1, mat2, xx, size);

    // rec(mat1, mat2, 1, xx, size);

    return xx;
}