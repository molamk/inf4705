#include "progdyn2.h"
#include <climits>

void solveProgDyn2(Problem &p, vector<int> &v)
{
    bool *matrix = (bool *)malloc(sizeof(bool) * p.numberOfSticks * (p.weightLimit + 1));
    matrix[0] = true;

    for (int j = 1; j < p.weightLimit + 1; j++)
        matrix[j] = p.sticks[0].second == j;

    for (int i = 1; i < p.numberOfSticks; i++)
    {
        int idx = (i - 1) * (p.weightLimit + 1);
        for (int j = 0; j < p.weightLimit + 1; j++)
            matrix[i * (p.weightLimit + 1) + j] = matrix[idx + j] || p.sticks[i].second <= j && matrix[idx + j - p.sticks[i].second];
    }

    // Backtracking
    int j = p.weightLimit;
    int i = p.numberOfSticks - 1;
    while (j > 0)
    {
        while (i > 0 && matrix[(i - 1) * (p.weightLimit + 1) + j])
            i--;

        j -= p.sticks[i].second;

        if (j >= 0)
            v.push_back(p.sticks[i--].first);
    }

    free(matrix);
}
