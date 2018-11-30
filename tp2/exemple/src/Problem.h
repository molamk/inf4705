#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>

using namespace std;

class Problem
{
public:
  int numberOfSticks;
  int weightLimit;
  vector<pair<int, int>> sticks;
};

#endif