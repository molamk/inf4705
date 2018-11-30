#include "ProgramArguments.h"
#include "glouton.h"
#include "progdyn1.h"
#include "progdyn2.h"
#include "recuit.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */

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
        else if (options._algorithm == "progdyn2")
        {
            begin_time = clock();
            solveProgDyn2(p, result);
        }
        else if (options._algorithm == "recuit")
        {
            double T = 5;
            int kmax = 5;
            int P = 100;
            double a = .2;
            begin_time = clock();
            solveRecuit(p, result, T, kmax, P, a);
        }

        double duration = (double(clock() - begin_time) / CLOCKS_PER_SEC);

        if (options._isPrintResult)
            printVector(result);

        cout.precision(20);
        if (options._isPrintTime)
            cout << fixed << (duration * 1000) << endl;

        if (options._isPrintSum)
        {
            int sum = 0;
            for (size_t i = 0; i < result.size(); i++)
                sum += p.sticks[result[i] - 1].second;
            cout << sum << endl;
        }
    }
    else
        cout << options._errorMessage << endl;
}