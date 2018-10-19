#include "main.h"

main(int argc, char *argv[])
{
    ProgramArguments options(argc, argv);

    if (!options.isValid())
    {
        cerr << options.getErrorMessage() << endl;
        return -1;
    }

    vector<int> matrix1 = readMatrixFromFile(options.getFirstMatrixPath());
    vector<int> matrix2 = readMatrixFromFile(options.getSecondMatrixPath());

    string algorithm = options.getAlgorithm();
    vector<int> result;

    clock_t begin_time;

    if (algorithm == "conv")
    {
        begin_time = clock();
        result = multiplyConv(matrix1, matrix2);
    }
    else if (algorithm == "strassen")
    {
        begin_time = clock();
        result = multiplyStrassen(matrix1, matrix2);
    }
    else if (algorithm == "strassenSeuil")
    {
        begin_time = clock();
        result = multiplyStrassenSeuil(matrix1, matrix2);
    }

    double duration = (double(clock() - begin_time) / CLOCKS_PER_SEC);

    if (options.isPrintMatrix())
        printMatrix(result);

    cout.precision(20);
    if (options.isPrintTime())
        cout << fixed << (duration * 1000) << endl;

    return 0;
}
