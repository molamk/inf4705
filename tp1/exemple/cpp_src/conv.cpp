#include <vector>
#include <ctime>
#include "multiplier.h"

using namespace std;

vector<vector<float>> multiplyConv(vector<vector<float>> &mat1, vector<vector<float>> &mat2)
{
    vector<vector<float>> result;
    int len = mat1.size();

    for (size_t i = 0; i < len; i++)
    {
        vector<float> row;
        for (size_t j = 0; j < len; j++)
        {
            float curr = 0;
            for (size_t k = 0; k < len; k++)
            {
                curr += mat1[i][k] * mat2[k][j];
            }
            row.push_back(curr);
        }
        result.push_back(row);
    }

    return result;
}