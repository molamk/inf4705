#ifndef PROGRAM_ARGUMENTS_H
#define PROGRAM_ARGUMENTS_H

#include "utils.h"

using namespace std;

class ProgramArguments
{
public:
  ProgramArguments(int argc, char *argv[]);
  bool isPrintMatrix();
  bool isPrintTime();
  bool isValid();
  string getErrorMessage();
  string getFirstMatrixPath();
  string getSecondMatrixPath();
  string getAlgorithm();

private:
  string _algorithm;
  string _firstMatrixPath;
  string _secondMatrixPath;
  bool _isPrintMatrix = false;
  bool _isPrintTime = false;
  bool _isValid = true;
  string _errorMessage;
};

#endif