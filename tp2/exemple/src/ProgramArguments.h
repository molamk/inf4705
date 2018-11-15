#ifndef PROGRAM_ARGUMENTS_H
#define PROGRAM_ARGUMENTS_H

#include "utils.h"

using namespace std;

class ProgramArguments
{
  public:
    string _algorithm;
    string _filename;
    bool _isPrintResult = false;
    bool _isPrintTime = false;
    bool _isPrintSum = false;
    bool _isValid = true;
    string _errorMessage;
    ProgramArguments(int argc, char *argv[]);
};

#endif