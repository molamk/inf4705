#include "multiplier.h"
using namespace std;

int multiply(int argc, char *argv[], function<vector<int>(vector<int> &, vector<int> &)> multiplier)
{
    ProgramArguments options(argc, argv);

    if (!options.isValid())
    {
        cerr << options.getErrorMessage() << endl;
        return -1;
    }

    vector<int> matrix1 = readMatrixFromFile(options.getFirstMatrixPath());
    vector<int> matrix2 = readMatrixFromFile(options.getSecondMatrixPath());

    const clock_t begin_time = clock();
    vector<int> result = multiplier(matrix1, matrix2);
    const double duration = (double(clock() - begin_time) / CLOCKS_PER_SEC);

    if (options.isPrintMatrix())
        printMatrix(result);

    cout.precision(20);
    if (options.isPrintTime())
        cout << fixed << (duration * 1000) << endl;

    return 0;
}