#ifndef UTILS_H
#define UTILS_H

#include "Problem.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <sys/stat.h>

using namespace std;

bool isFileExists(const std::string &name);
vector<string> split(const string &s, char delim);
string readFileRaw(const string &filename);
void parseRaw(const string &raw, Problem &p);
bool comparePairs(const pair<int, int> &a, const pair<int, int> &b);
void sortSticks(vector<pair<int, int>> &v);
void printVector(vector<int> &v);
void printSticks(vector<pair<int, int>> &v);

#endif