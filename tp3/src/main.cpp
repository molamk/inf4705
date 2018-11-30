#include "utils.h"
#include "greedy.h"
#include "recuit.h"
#include <time.h>

int main()
{
    srand(time(NULL));

    // The edges list is a symmertrical matrix => Optimize !!
    const std::string filename = "../instances/PCT_200_50";
    Problem p;
    createProblem(filename, p);

    std::vector<int> s;
    solveGreedy(p, s);

    std::cout << std::endl;
    std::cout << "Value ratio:\t" << getValueRatio(p, s) << std::endl;
    std::cout << "Duration ratio:\t" << getDurationRatio(p, s) << std::endl;

    std::vector<int> recuit_s;
    solveRecuit(p, recuit_s);

    std::cout << std::endl;
    std::cout << "Value ratio:\t" << getValueRatio(p, recuit_s) << std::endl;
    std::cout << "Duration ratio:\t" << getDurationRatio(p, recuit_s) << std::endl;

    return 0;
}