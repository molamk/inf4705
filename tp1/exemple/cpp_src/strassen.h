#ifndef STRASSEN_H
#define STRASSEN_H

#include <vector>
#include "conv.h"
#include "ProgramArguments.h"
#include "multiplier.h"
#include <functional>

using namespace std;
using f_matrix = vector<vector<float>>;

class MatrixAllocator
{
  public:
    MatrixAllocator();
    MatrixAllocator(size_t size);
    f_matrix load(int size);

  private:
    f_matrix m;
};

void addMatrices(
    vector<vector<float>> &m1,
    vector<vector<float>> &m2,
    vector<vector<float>> &x);

void substractMatrices(
    vector<vector<float>> &m1,
    vector<vector<float>> &m2,
    vector<vector<float>> &x);

void strassenSplit(vector<vector<float>> &source,
                   vector<vector<float>> &x11,
                   vector<vector<float>> &x12,
                   vector<vector<float>> &x21,
                   vector<vector<float>> &x22);

void strassenMerge(
    vector<vector<float>> &c11,
    vector<vector<float>> &c12,
    vector<vector<float>> &c21,
    vector<vector<float>> &c22,
    vector<vector<float>> &target);

void rec(vector<vector<float>> &mat1, vector<vector<float>> &mat2, uint64_t threshold, vector<vector<float>> &result, int size, MatrixAllocator *m_allocator);

vector<vector<float>> multiplyStrassen(vector<vector<float>> &mat1, vector<vector<float>> &mat2);
#endif