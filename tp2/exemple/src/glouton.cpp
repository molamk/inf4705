#include "glouton.h"

void solveGreedy(Problem &p, vector<int> &v)
{
    sortSticks(p.sticks);
    int weightLimit = p.weightLimit;

    for (int i = 0; i < p.numberOfSticks; i++)
    {
        if (p.sticks[i].second < weightLimit)
        {
            weightLimit -= p.sticks[i].second;
            v.push_back(p.sticks[i].first);
        }
    }
}