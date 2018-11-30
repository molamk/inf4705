#if !defined(RECUIT_H)
#define RECUIT_H

#include "utils.h"
#include "glouton.h"
#include <cmath>
#include <unordered_map>

using namespace std;

vector<int> nextSolution(
    Problem &p,
    vector<int> &input);

vector<int> recuit(
    Problem &p,
    vector<int> s0,
    double T,
    int kmax,
    int P,
    double a);

void solveRecuit(Problem &p,
                 vector<int> &v,
                 double T,
                 int kmax,
                 int P,
                 double a);

#endif // RECUIT_H
