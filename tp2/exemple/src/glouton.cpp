#include "glouton.h"

void solveGreedy(Problem &p, vector<int> &v)
{
    vector<pair<int, int>> s = p.sticks;
    sortSticks(s);
    int weightLimit = p.weightLimit;

    for (int i = 0; i < p.numberOfSticks; i++)
    {
        if (s[i].second < weightLimit)
        {
            weightLimit -= s[i].second;
            v.push_back(s[i].first);
        }
    }
}