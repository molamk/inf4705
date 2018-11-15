#include "recuit.h"

void solveRecuit(Problem &p, vector<int> &result)
{
    vector<int> s0;
    solveGreedy(p, s0);

    double T = 100;
    int kmax = 10;
    int P = 10;
    double a = .5;

    result = recuit(p, s0, T, kmax, P, a);
}

vector<int> recuit(
    Problem &p,
    vector<int> s0,
    double T,
    int kmax,
    int P,
    double a)
{
    vector<int> s = s0;
    vector<int> betterSolution = s;
    vector<int> sPrime;
    std::vector<int> hello_vector(5);
    std::cout << hello_vector.size() << std::endl;

    double theta = T;
    for (int k = 1; k < kmax; k++)
    {
        for (int j = 1; j < P; j++)
        {
            sPrime = nextSolution(p, s);
            int delta = sumVector(sPrime) - sumVector(s);
            if (delta >= 0 || exp(delta / theta) > ((double)rand() / RAND_MAX))
            {
                s = sPrime;
                if (sumVector(s) > sumVector(betterSolution))
                    betterSolution = s;
            }
        }
        theta *= a;
    }

    return betterSolution;
}

vector<int> nextSolution(
    Problem &p,
    vector<int> &input)
{
    vector<int> solution = input;
    unordered_map<int, int> sticksMap;
    for (pair<int, int> s : p.sticks)
        sticksMap.insert(s);

    int sum = 0;
    unordered_map<int, int> solutionMap;
    for (int s : solution)
    {
        int weight = sticksMap.find(s)->second;
        solutionMap.insert(make_pair(s, weight));
        sum += weight;
    }

    // Find a stick that's not in the solution
    int randomIdx;
    do
    {
        randomIdx = rand() % p.sticks.size();
    } while (solutionMap.find(p.sticks[randomIdx].first) != solutionMap.end());

    solution.push_back(p.sticks[randomIdx].first);
    solutionMap.insert(p.sticks[randomIdx]);
    sum += p.sticks[randomIdx].second;

    // Remove sticks while the total weight is more than the target
    while (sum > p.weightLimit)
    {
        int randomIdx = rand() % solution.size();
        unordered_map<int, int>::iterator it = solutionMap.find(solution[randomIdx]);
        sum -= it->second;
        solution.erase(remove(solution.begin(), solution.end(), it->first), solution.end());
        solutionMap.erase(it);
    }

    return solution;
}
