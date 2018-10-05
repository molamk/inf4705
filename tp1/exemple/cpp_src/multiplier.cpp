#include "multiplier.h"
using namespace std;

int multiply(int argc, char *argv[], function<vector<vector<float>>(vector<vector<float>> &, vector<vector<float>> &)> multiplier)
{
    ProgramArguments options(argc, argv);

    if (!options.isValid())
    {
        cerr << options.getErrorMessage() << endl;
        return -1;
    }

    vector<vector<float>> matrix1 = readMatrixFromFile(options.getFirstMatrixPath());
    vector<vector<float>> matrix2 = readMatrixFromFile(options.getSecondMatrixPath());

    const clock_t begin_time = clock();
    vector<vector<float>> result = multiplier(matrix1, matrix2);
    const double duration = (double(clock() - begin_time) / CLOCKS_PER_SEC);

    if (options.isPrintMatrix())
        printMatrix(result);

    cout.precision(20);
    if (options.isPrintTime())
        cout << fixed << duration << endl;

    return 0;
}