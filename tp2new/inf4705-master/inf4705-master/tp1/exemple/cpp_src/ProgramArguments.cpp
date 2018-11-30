#include "ProgramArguments.h"

ProgramArguments::ProgramArguments(int argc, char *argv[])
{
    if (argc < 4)
    {
        _isValid = false;
        _errorMessage = "Insufficient arguments";
    }
    else
    {
        _algorithm = argv[1];

        if (_algorithm != "conv" && _algorithm != "strassen" && _algorithm != "strassenSeuil")
        {
            _isValid = false;
            _errorMessage = "Algorithm " + _algorithm + " not supported";
        }

        _firstMatrixPath = formatMatrixFileName(argv[2]);
        if (!isFileExists(_firstMatrixPath))
        {
            _isValid = false;
            _errorMessage = "File " + _firstMatrixPath + " not found";
        }

        _secondMatrixPath = formatMatrixFileName(argv[3]);
        if (!isFileExists(_secondMatrixPath))
        {
            _isValid = false;
            _errorMessage = "File " + _secondMatrixPath + " not found";
        }

        if (argc >= 5)
        {
            string third = argv[4];
            if (third == "-p")
                _isPrintMatrix = true;
            else if (third == "-t")
                _isPrintTime = true;
            else
            {
                _isValid = false;
                _errorMessage = "Invalid option " + third;
            }
        }

        if (argc == 6)
        {
            string fourth = argv[5];
            if (fourth == "-p" && !_isPrintMatrix)
                _isPrintMatrix = true;
            else if (fourth == "-t" && !_isPrintTime)
                _isPrintTime = true;

            else
            {
                _isValid = false;
                _errorMessage = "Invalid option " + fourth;
            }
        }
    }
}

bool ProgramArguments::isPrintMatrix()
{
    return _isPrintMatrix;
}

bool ProgramArguments::isPrintTime()
{
    return _isPrintTime;
}

bool ProgramArguments::isValid()
{
    return _isValid;
}

string ProgramArguments::getErrorMessage()
{
    return _errorMessage;
}

string ProgramArguments::getFirstMatrixPath()
{
    return _firstMatrixPath;
}

string ProgramArguments::getSecondMatrixPath()
{
    return _secondMatrixPath;
}

string ProgramArguments::getAlgorithm()
{
    return _algorithm;
}