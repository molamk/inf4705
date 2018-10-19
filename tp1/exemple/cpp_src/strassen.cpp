#include <vector>
#include <ctime>
#include "multiplier.h"
#include "conv.h"
#include <cmath>

using namespace std;
using f_matrix = vector<vector<float>>;

void addMatrices(
    f_matrix &m1,
    f_matrix &m2,
    f_matrix &x,
    int size)
{
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            x[i][j] = m1[i][j] + m2[i][j];
}

void substractMatrices(
    f_matrix &m1,
    f_matrix &m2,
    f_matrix &x,
    int size)
{
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            x[i][j] = m1[i][j] - m2[i][j];
}

void strassenSplit(const f_matrix &source,
                   f_matrix &x11,
                   f_matrix &x12,
                   f_matrix &x21,
                   f_matrix &x22,
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
    f_matrix &c11,
    f_matrix &c12,
    f_matrix &c21,
    f_matrix &c22,
    f_matrix &target,
    int half)
{
    // cout << target.size() << endl;
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

void ikjalgorithm(const f_matrix &A,
                  const f_matrix &B,
                  f_matrix &C,
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

class MatrixAllocator
{
  public:
    MatrixAllocator() {}
    MatrixAllocator(size_t size)
    {
        _size = size;
        size_t i = size;
        while (i > 0)
        {
            vector<float> row(i);
            f_matrix matrix(i, row);
            _all_matrices.push_back(matrix);
            i /= 2;
        }
    }

    vector<f_matrix> getList()
    {
        return _all_matrices;
    }

    f_matrix create(int size)
    {
        vector<float> row(size);
        f_matrix matrix(size, row);
        return matrix;
    }

    f_matrix load(int size)
    {
        int idx = log2(_size / size);
        return _all_matrices[idx];
    }

    void fresh_load(f_matrix &target, int size)
    {
        vector<float> row(size);
        f_matrix matrix(size, row);
        // int idx = log2(_size / size);
        // return _all_matrices[idx];
        target = matrix;
    }

    f_matrix load_new(int size)
    {
        vector<float> row(size);
        f_matrix matrix(size, row);

        return matrix;
    }

    void ref_load(f_matrix &target, int size)
    {
        int idx = log2(_size / size);
        // cout << "idx\t" << idx << endl;
        target = _all_matrices[idx];
    }

  private:
    int _size;
    vector<f_matrix> _all_matrices;
};

class FancyStrassen
{
  public:
    FancyStrassen(size_t size)
    {
        _m_allocator = new MatrixAllocator(size);

        int half = size / 2;
        vector<float> inside(half);
        f_matrix a11(half, inside);
        _a11 = a11;
        f_matrix a12(half, inside);
        _a12 = a12;
        f_matrix a21(half, inside);
        _a21 = a21;
        f_matrix a22(half, inside);
        _a22 = a22;
        f_matrix b11(half, inside);
        _b11 = b11;
        f_matrix b12(half, inside);
        _b12 = b12;
        f_matrix b21(half, inside);
        _b21 = b21;
        f_matrix b22(half, inside);
        _b22 = b22;
        f_matrix c11(half, inside);
        _c11 = c11;
        f_matrix c12(half, inside);
        _c12 = c12;
        f_matrix c21(half, inside);
        _c21 = c21;
        f_matrix c22(half, inside);
        _c22 = c22;
        f_matrix m1(half, inside);
        _m1 = m1;
        f_matrix m2(half, inside);
        _m2 = m2;
        f_matrix m3(half, inside);
        _m3 = m3;
        f_matrix m4(half, inside);
        _m4 = m4;
        f_matrix m5(half, inside);
        _m5 = m5;
        f_matrix m6(half, inside);
        _m6 = m6;
        f_matrix m7(half, inside);
        _m7 = m7;
        f_matrix aResult(half, inside);
        _aResult = aResult;
        f_matrix bResult(half, inside);
        _bResult = bResult;
    }

    void clean()
    {
        free(_m_allocator);
    }

    void rec(const f_matrix &mat1,
            //  int i_1,
            //  int j_1,
             const f_matrix &mat2,
            //  int i_2,
            //  int j_2,
             f_matrix &result,
             uint64_t threshold,
             int size)
    {
        // int n = mat1.size();
        int half = size / 2;

        if (size <= threshold)
        {
            ikjalgorithm(mat1, mat2, result, size);
        }
        else
        {
            strassenSplit(mat1, _a11, _a12, _a21, _a22, half);
            strassenSplit(mat2, _b11, _b12, _b21, _b22, half);

            addMatrices(_a11, _a22, _aResult, half);
            addMatrices(_b11, _b22, _bResult, half);
            rec(_aResult, _bResult, _m1, threshold, half);

            addMatrices(_a21, _a22, _aResult, half);
            rec(_aResult, _b11, _m2, threshold, half);

            substractMatrices(_b12, _b22, _bResult, half);
            rec(_a11, _bResult, _m3, threshold, half);

            substractMatrices(_b21, _b11, _bResult, half);
            rec(_a22, _bResult, _m4, threshold, half);

            addMatrices(_a11, _a12, _aResult, half);
            rec(_aResult, _b22, _m5, threshold, half);

            substractMatrices(_a21, _a11, _aResult, half);
            addMatrices(_b11, _b12, _bResult, half);
            rec(_aResult, _bResult, _m6, threshold, half);

            substractMatrices(_a12, _a22, _aResult, half);
            addMatrices(_b21, _b22, _bResult, half);
            rec(_aResult, _bResult, _m7, threshold, half);

            addMatrices(_m3, _m5, _c12, half);
            addMatrices(_m2, _m4, _c21, half);

            addMatrices(_m1, _m4, _aResult, half);
            addMatrices(_aResult, _m7, _bResult, half);
            substractMatrices(_bResult, _m5, _c11, half);

            addMatrices(_m1, _m3, _aResult, half);
            addMatrices(_aResult, _m6, _bResult, half);
            substractMatrices(_bResult, _m2, _c22, half);

            strassenMerge(_c11, _c12, _c21, _c22, result, half);
        }
    }

  private:
    MatrixAllocator *_m_allocator;
    f_matrix _a11;
    f_matrix _a12;
    f_matrix _a21;
    f_matrix _a22;
    f_matrix _b11;
    f_matrix _b12;
    f_matrix _b21;
    f_matrix _b22;
    f_matrix _c11;
    f_matrix _c12;
    f_matrix _c21;
    f_matrix _c22;
    f_matrix _m1;
    f_matrix _m2;
    f_matrix _m3;
    f_matrix _m4;
    f_matrix _m5;
    f_matrix _m6;
    f_matrix _m7;
    f_matrix _aResult;
    f_matrix _bResult;
};

void rec(f_matrix &mat1,
         f_matrix &mat2,
         uint64_t threshold,
         f_matrix &result,
         int size,
         MatrixAllocator *m_allocator)
{
    int n = mat1.size();
    int half = n / 2;

    if (n <= threshold)
    {
        ikjalgorithm(mat1, mat2, result, size);
    }
    else
    {
        f_matrix a11;
        f_matrix a12;
        f_matrix a21;
        f_matrix a22;
        f_matrix b11;
        f_matrix b12;
        f_matrix b21;
        f_matrix b22;
        f_matrix c11;
        f_matrix c12;
        f_matrix c21;
        f_matrix c22;
        f_matrix m1;
        f_matrix m2;
        f_matrix m3;
        f_matrix m4;
        f_matrix m5;
        f_matrix m6;
        f_matrix m7;
        f_matrix aResult;
        f_matrix bResult;

        vector<float> inside(half);
        m_allocator->ref_load(a11, half);
        m_allocator->ref_load(a12, half);
        m_allocator->ref_load(a21, half);
        m_allocator->ref_load(a22, half);
        m_allocator->ref_load(b11, half);
        m_allocator->ref_load(b12, half);
        m_allocator->ref_load(b21, half);
        m_allocator->ref_load(b22, half);
        m_allocator->ref_load(c11, half);
        m_allocator->ref_load(c12, half);
        m_allocator->ref_load(c21, half);
        m_allocator->ref_load(c22, half);
        m_allocator->ref_load(m1, half);
        m_allocator->ref_load(m2, half);
        m_allocator->ref_load(m3, half);
        m_allocator->ref_load(m4, half);
        m_allocator->ref_load(m5, half);
        m_allocator->ref_load(m6, half);
        m_allocator->ref_load(m7, half);
        m_allocator->ref_load(aResult, half);
        m_allocator->ref_load(bResult, half);

        strassenSplit(mat1, a11, a12, a21, a22, half);
        strassenSplit(mat2, b11, b12, b21, b22, half);

        addMatrices(a11, a22, aResult, half);
        addMatrices(b11, b22, bResult, half);
        rec(aResult, bResult, threshold, m1, half, m_allocator);

        addMatrices(a21, a22, aResult, half);
        rec(aResult, b11, threshold, m2, half, m_allocator);

        substractMatrices(b12, b22, bResult, half);
        rec(a11, bResult, threshold, m3, half, m_allocator);

        substractMatrices(b21, b11, bResult, half);
        rec(a22, bResult, threshold, m4, half, m_allocator);

        addMatrices(a11, a12, aResult, half);
        rec(aResult, b22, threshold, m5, half, m_allocator);

        substractMatrices(a21, a11, aResult, half);
        addMatrices(b11, b12, bResult, half);
        rec(aResult, bResult, threshold, m6, half, m_allocator);

        substractMatrices(a12, a22, aResult, half);
        addMatrices(b21, b22, bResult, half);
        rec(aResult, bResult, threshold, m7, half, m_allocator);

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

f_matrix multiplyStrassen(f_matrix &mat1, f_matrix &mat2)
{
    vector<float> inner(mat1.size());
    f_matrix result(mat1.size(), inner);
    uint64_t threshold = 1;
    MatrixAllocator m_allocator(mat1.size());
    FancyStrassen f(mat1.size());
    f.rec(mat1, mat2, result, threshold, mat1.size());
    f.clean();

    // rec(mat1, mat2, threshold, result, mat1.size(), &m_allocator);

    return result;
}