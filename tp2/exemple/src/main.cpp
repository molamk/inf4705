#include "ProgramArguments.h"
#include "glouton.h"
#include "progdyn1.h"

using namespace std;

int main(int argc, char *argv[])
{
    ProgramArguments options(argc, argv);

    if (options._isValid)
    {
        Problem p;
        vector<int> result;
        string raw = readFileRaw(options._filename);
        parseRaw(raw, p);

        clock_t begin_time;

        if (options._algorithm == "glouton")
        {
            begin_time = clock();
            solveGreedy(p, result);
        }
        else if (options._algorithm == "progdyn1")
        {
            begin_time = clock();
            solveProgDyn1(p, result);
        }

        double duration = (double(clock() - begin_time) / CLOCKS_PER_SEC);

        if (options._isPrintResult)
            printVector(result);

        cout.precision(20);
        if (options._isPrintTime)
            cout << fixed << (duration * 1000) << endl;

        int sum = 0;
        for (int x : result)
            sum += x;

        cout << "Sum:\t" << sum << endl;
    }
    else
    {
        cout << options._errorMessage << endl;
    }
}