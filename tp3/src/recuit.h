#if !defined(RECUIT_H)
#define RECUIT_H

#include "utils.h"
#include "greedy.h"

void solveRecuit(Problem &p, std::vector<int> &s);
std::vector<int> next(Problem &p, std::vector<int> &prev);
std::vector<int> recuit(
    Problem &p,
    double T,
    int kmax,
    int P,
    double a);

#endif // RECUIT_H
