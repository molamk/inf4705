#include "ProgramArguments.h"

int isValidAlgorithm(string algorithm)
{
    return algorithm == "glouton" ||
           algorithm == "progdyn1" ||
           algorithm == "progdyn2" ||
           algorithm == "recuit";
}

int getFlagIndex(int argc, char *argv[], string flag)
{
    int algorithmFlagIdx = -1;
    for (int i = 0; i < argc && algorithmFlagIdx == -1; i++)
        if (string(argv[i]) == flag)
            algorithmFlagIdx = i;

    return algorithmFlagIdx;
}

ProgramArguments::ProgramArguments(int argc, char *argv[])
{

    // Algorithm
    int algorithmFlagIdx = getFlagIndex(argc, argv, "-a");

    if (algorithmFlagIdx == -1 ||
        algorithmFlagIdx == argc - 1 ||
        !isValidAlgorithm(argv[algorithmFlagIdx + 1]))
    {
        _isValid = false;
        _errorMessage = "Invalid algorithm";
        return;
    }

    _algorithm = argv[algorithmFlagIdx + 1];

    // Path
    int filenameFlagIdx = getFlagIndex(argc, argv, "-e");
    if (filenameFlagIdx == -1 ||
        filenameFlagIdx == argc - 1 ||
        !isFileExists(argv[filenameFlagIdx + 1]))
    {
        _isValid = false;
        _errorMessage = "Exemplaire file not found";
        return;
    }

    _filename = argv[filenameFlagIdx + 1];

    // Print result
    _isPrintResult = getFlagIndex(argc, argv, "-p") != -1;

    // Print time
    _isPrintTime = getFlagIndex(argc, argv, "-t") != -1;

    // Print sum
    _isPrintSum = getFlagIndex(argc, argv, "-s") != -1;
};