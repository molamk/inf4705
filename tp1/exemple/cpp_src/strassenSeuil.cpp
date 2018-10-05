#include "strassenSeuil.h"

using namespace std;

vector<vector<float>> multiplyStrassenSeuil(vector<vector<float>> &mat1, vector<vector<float>> &mat2)
{
    int size = mat1.size();
    vector<float> x(size);
    vector<vector<float>> xx(size, x);
    rec(mat1, mat2, 150, xx, size);

    return xx;
}