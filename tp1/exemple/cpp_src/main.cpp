#include "main.h"

main(int argc, char *argv[])
{
    ProgramArguments options(argc, argv);

    if (!options.isValid())
    {
        cout << options.getErrorMessage() << endl;
        return -1;
    }

    string algorithm = options.getAlgorithm();

    if (algorithm == "conv")
    {
        return multiply(argc, argv, multiplyConv);
    }
    else if (algorithm == "strassen")
    {
        return multiply(argc, argv, multiplyStrassen);
    }
    else
    {
        return multiply(argc, argv, multiplyStrassenSeuil);
    }
}
