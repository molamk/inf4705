#include "greedy.h"

void solveGreedy(Problem &p, std::vector<int> &solution)
{
    std::unordered_set<int> s;
    for (int i = 0; i < p.vertices.size(); i++)
        s.insert(i);

    int remainingDuration = p.maxDuration;
    int idx = 0;

    while (remainingDuration >= 0 && !s.empty())
    {
        solution.push_back(idx);
        int prevDuration = p.edges[0][idx];
        remainingDuration -= prevDuration;

        s.erase(s.find(idx));

        float maxRatio = 0;
        int prevIdx = idx;
        for (auto it = s.begin(); it != s.end(); ++it)
        {
            int currentDuration = p.edges[prevIdx][*it];
            float currentRatio = (float)p.vertices[*it] / currentDuration;
            if (currentRatio > maxRatio &&
                remainingDuration > p.edges[0][*it])
            {
                maxRatio = currentRatio;
                prevDuration = currentDuration;
                idx = *it;
            }
        }

        if (maxRatio == 0)
            break;
    }

    solution.push_back(0);
    remainingDuration -= p.edges[0][solution[solution.size() - 1]];
}