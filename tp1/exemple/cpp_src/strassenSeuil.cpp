#include "strassenSeuil.h"

using namespace std;

vector<vector<float>> multiplyStrassenSeuil(vector<vector<float>> &mat1, vector<vector<float>> &mat2)
{
    return rec(mat1, mat2, 150);
}