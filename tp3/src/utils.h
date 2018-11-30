#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include <unordered_map>
#include <cmath>
#include "Problem.h"

bool isFileExists(const std::string &name);
std::string readFileRaw(const std::string &fileName);
std::vector<std::string> split(const std::string &s, char delim);
void createProblem(const std::string &filename, Problem &p);
void printVector(std::vector<int> &v);
void printMatrix(std::vector<std::vector<int>> &m);
int getTotalValue(Problem &p, std::vector<int> &s);
int getTotalDuration(Problem &p, std::vector<int> &s);
float getValueRatio(Problem &p, std::vector<int> &s);
float getDurationRatio(Problem &p, std::vector<int> &s);
float getValueDurationRatio(Problem &p, std::vector<int> &s);

#endif