#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include <cmath>


using namespace std;

bool isFileExists(const std::string &name);

string formatDurationFileName(int size, string algo);

string formatMatrixFileName(string rawFileName);

string readFileRaw(const string &fileName);

vector<string> split(const string &s, char delim);

float stringToFloat(const string &str);

vector<int> formatMatrixFromRaw(const string &rawMatrix);

void printMatrix(const vector<int> &matrix);

vector<int> readMatrixFromFile(const string &filePath);

vector<float> getDurations(int size, string &algo);

float mean(vector<float> &durations);

#endif