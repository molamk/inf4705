#include "recuit.h"

std::vector<int> next(Problem &p, std::vector<int> &solution)
{
    int totalDuration = getTotalDuration(p, solution);
    std::vector<int> next = solution;

    std::unordered_set<int> m;
    for (auto &x : solution)
        m.insert(x);

    int randomNodeIdx;
    int randomNodeValue;
    int durationToRemove;
    int durationToAdd;

    do
    {
        randomNodeIdx = rand() % (solution.size() - 2) + 1;
        randomNodeValue = rand() % p.vertices.size();

        durationToRemove = p.edges[solution[randomNodeIdx]][solution[randomNodeIdx - 1]] +
                           p.edges[solution[randomNodeIdx]][solution[randomNodeIdx + 1]];

        durationToAdd = p.edges[randomNodeValue][solution[randomNodeIdx - 1]] +
                        p.edges[randomNodeValue][solution[randomNodeIdx + 1]];
    } while (m.find(randomNodeValue) != m.end() ||
             totalDuration - durationToRemove + durationToAdd > p.maxDuration);

    next[randomNodeIdx] = randomNodeValue;

    return next;
}

void solveRecuit(Problem &p, std::vector<int> &solution)
{
    double T = 0.5;
    double a = 0.5;
    int kmax = 100;
    int P = 100;

    solution = recuit(p, T, kmax, P, a);
}

std::vector<int> recuit(
    Problem &p,
    double T,
    int kmax,
    int P,
    double a)
{
    std::vector<int> s;
    solveGreedy(p, s);
    std::vector<int> betterSolution = s;
    std::vector<int> sPrime;

    double theta = T;
    for (int k = 1; k < kmax; k++)
    {
        for (int j = 1; j < P; j++)
        {
            sPrime = next(p, s);
            int delta = getTotalValue(p, sPrime) - getTotalValue(p, s);
            if (delta >= 0 || exp(delta / theta) >= ((double)rand() / RAND_MAX))
            {
                s = sPrime;
                if (getTotalValue(p, s) - getTotalValue(p, betterSolution) >= 0)
                    betterSolution = s;
            }
        }
        theta *= a;
    }

    return betterSolution;
}