#ifndef STRASSEN_H
#define STRASSEN_H

#include <vector>
#include "conv.h"
#include "ProgramArguments.h"
#include "multiplier.h"
#include <functional>

using namespace std;

class MatrixAllocator
{
  public:
    MatrixAllocator();
    MatrixAllocator(size_t size);
    vector<int> load(int size);

  private:
    vector<int> m;
};

void addMatrices(
    vector<int> &m1,
    vector<int> &m2,
    vector<int> &x);

void substractMatrices(
    vector<int> &m1,
    vector<int> &m2,
    vector<int> &x);

void strassenSplit(vector<int> &source,
                   vector<int> &x11,
                   vector<int> &x12,
                   vector<int> &x21,
                   vector<int> &x22,
                   int size);

void strassenMerge(
    vector<int> &c11,
    vector<int> &c12,
    vector<int> &c21,
    vector<int> &c22,
    vector<int> &target,
    int size);

void rec(vector<int> &mat1, vector<int> &mat2, uint64_t threshold, vector<int> &result, int size);
// void rec(vector<int> &mat1, vector<int> &mat2, uint64_t threshold, vector<int> &result, int size, MatrixAllocator *m_allocator);

vector<int> multiplyStrassen(vector<int> &mat1, vector<int> &mat2);
#endif