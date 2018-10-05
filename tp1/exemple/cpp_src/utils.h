#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/stat.h>

using namespace std;

bool isFileExists(const std::string &name);

string formatDurationFileName(int size, string algo);

string formatMatrixFileName(string rawFileName);

string readFileRaw(const string &fileName);

vector<string> split(const string &s, char delim);

float stringToFloat(const string &str);

vector<vector<float>> formatMatrixFromRaw(const string &rawMatrix);

void printMatrix(vector<vector<float>> &matrix);

vector<vector<float>> readMatrixFromFile(const string &filePath);

vector<float> getDurations(int size, string &algo);

float mean(vector<float> &durations);

#endif