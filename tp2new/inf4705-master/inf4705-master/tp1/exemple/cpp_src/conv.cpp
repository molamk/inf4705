#include <vector>
#include <ctime>
#include "multiplier.h"

using namespace std;

vector<int> multiplyConv(vector<int> &mat1, vector<int> &mat2)
{
    int len = mat1.size();
    vector<int> result(len);
    int rowSize = (int)sqrt(len);

    for (size_t i = 0; i < rowSize; i++)
    {
        for (size_t j = 0; j < rowSize; j++)
        {
            int curr = 0;
            for (size_t k = 0; k < rowSize; k++)
            {
                curr += mat1[i * rowSize + k] * mat2[k * rowSize + j];
            }
            result[i * rowSize + j] = curr;
        }
    }

    return result;
}