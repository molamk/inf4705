#if !defined(PROBLEM_H)
#define PROBLEM_H

#include <iostream>
#include <vector>

class Problem
{
  public:
    Problem() {}
    int maxDuration;
    std::vector<int> vertices;
    std::vector<std::vector<int>> edges;
};

#endif // PROBLEM_H
