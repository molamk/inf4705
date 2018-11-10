#include "progdyn1.h"

void backTrack(int idx,
               vector<int> &indeces,
               vector<pair<int, int>> &inputSticks,
               vector<int> &result)
{
    if (indeces[idx] < 0)
        result.push_back(inputSticks[-indeces[idx]].first);
    else
    {
        backTrack(indeces[idx], indeces, inputSticks, result);
        backTrack(idx - indeces[idx], indeces, inputSticks, result);
    }
}

void solveProgDyn1(Problem &p, vector<int> &v)
{
    vector<int> numbersOfSticks(p.weightLimit);
    vector<int> indeces(p.weightLimit);

    for (int i = 0; i < p.weightLimit; i++)
        numbersOfSticks[i] = __INT_MAX__;

    for (int i = 0; i < p.numberOfSticks; i++)
    {
        numbersOfSticks[p.sticks[i].second - 1] = 1;
        indeces[p.sticks[i].second - 1] = -i;
    }

    for (int j = 0; j < p.weightLimit; j++)
        if (numbersOfSticks[j] != 1)
            for (int i = 0; i < (int)(j / 2); i++)
                if (numbersOfSticks[j] > numbersOfSticks[i] + numbersOfSticks[j - i] &&
                    // Handle overflow
                    numbersOfSticks[i] != __INT_MAX__ && numbersOfSticks[j - i] != __INT_MAX__)
                {
                    numbersOfSticks[j] = numbersOfSticks[i] + numbersOfSticks[j - i];
                    indeces[j] = i;
                }

    int startIdx = p.weightLimit - 1;

    while (indeces[startIdx] == 0 && startIdx >= 0)
        startIdx--;

    backTrack(startIdx, indeces, p.sticks, v);
}
