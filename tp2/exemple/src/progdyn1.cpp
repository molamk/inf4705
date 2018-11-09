#include "progdyn1.h"

void backTrack(int idx,
               vector<int> &indeces,
               vector<pair<int, int>> &inputSticks,
               vector<pair<int, int>> &outputSticks)
{
    int target = indeces[idx];
    if (target < 0)
    {
        outputSticks.push_back(inputSticks[-target]);
    }
    else
    {
        backTrack(target, indeces, inputSticks, outputSticks);
        backTrack(idx - target, indeces, inputSticks, outputSticks);
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
    {
        if (numbersOfSticks[j] != 1)
        {
            for (int i = 0; i < (int)(j / 2); i++)
            {
                if (numbersOfSticks[j] > numbersOfSticks[i] + numbersOfSticks[j - i] &&
                    // Handle overflow
                    numbersOfSticks[i] != __INT_MAX__ && numbersOfSticks[j - i] != __INT_MAX__)
                {
                    numbersOfSticks[j] = numbersOfSticks[i] + numbersOfSticks[j - i];
                    indeces[j] = i;
                }
            }
        }
    }

    vector<pair<int, int>> result;
    backTrack(p.weightLimit - 1, indeces, p.sticks, result);
    for (pair<int, int> r : result)
    {
        v.push_back(r.second);
    }
}
