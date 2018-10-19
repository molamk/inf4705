#ifndef MULTIPLIER_H
#define MULTIPLIER_H

#include "utils.h"
#include "ProgramArguments.h"
#include <vector>
#include <functional>

using namespace std;

int multiply(int argc, char *argv[], function<vector<int>(vector<int> &, vector<int> &)> multiplier);

#endif