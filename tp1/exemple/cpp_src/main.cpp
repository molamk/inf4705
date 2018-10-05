#include "main.h"

main(int argc, char *argv[])
{
    ProgramArguments options(argc, argv);

    if (!options.isValid())
    {
        cerr << options.getErrorMessage() << endl;
        return -1;
    }

    vector<vector<float>> matrix1 = readMatrixFromFile(options.getFirstMatrixPath());
    vector<vector<float>> matrix2 = readMatrixFromFile(options.getSecondMatrixPath());

    string algorithm = options.getAlgorithm();
    vector<vector<float>> result;

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

    const double duration = (double(clock() - begin_time) / CLOCKS_PER_SEC);

    if (options.isPrintMatrix())
        printMatrix(result);

    cout.precision(20);
    if (options.isPrintTime())
        cout << fixed << duration << endl;

    return 0;
}
