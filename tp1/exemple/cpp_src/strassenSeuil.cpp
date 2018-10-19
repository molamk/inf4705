#include "strassenSeuil.h"

using namespace std;

vector<int> multiplyStrassenSeuil(vector<int> &mat1, vector<int> &mat2)
{
    int size = mat1.size();
    vector<int> result(size);
    uint64_t threshold = size / 2;

    rec(mat1, mat2, threshold, result, size);

    return result;
}