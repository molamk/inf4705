#include "progdyn2.h"

void solveProgDyn2(Problem &p, vector<int> &v)
{
    // Initialiser le tableau 2D
    int *matrix = (int *)malloc(sizeof(int) * p.numberOfSticks * p.weightLimit);
    // int **matrix = (int **)malloc(sizeof(int *) * p.numberOfSticks);
    // for (int x = 0; x < p.numberOfSticks; x++)
    //     matrix[x] = (int *)calloc(p.weightLimit, sizeof(int));

    for (int i = 0; i < p.numberOfSticks; i++)
    {
        matrix[i * p.numberOfSticks + p.sticks[i].second] = 1;
        matrix[i * p.numberOfSticks + 0] = 0;
    }

    for (int i = 0; i < p.numberOfSticks; i++)
    {
        for (int j = 1; j < p.weightLimit + 1; j++)
        {
            int firstIdx = j - p.sticks[i].second;
            // Handle overflow
            int first = firstIdx < 0 ? __INT_MAX__ : (matrix[i * p.numberOfSticks + firstIdx] == __INT_MAX__ ? __INT_MAX__ : 1 + matrix[i * p.numberOfSticks + firstIdx]);

            int secondIdx = i - 1;
            int second = secondIdx < 0 ? __INT_MAX__ : matrix[secondIdx * p.numberOfSticks + j];

            matrix[i * p.numberOfSticks + j] = first < second ? first : second;
        }
    }

    // Back-tracking
    int i = p.numberOfSticks - 1;
    int j = p.weightLimit;

    while (i >= 0 && j >= 0)
    {
        int leftIdx = j - p.sticks[i].second;
        int left = leftIdx < 0 ? __INT_MAX__ : (matrix[i * p.numberOfSticks + leftIdx] == __INT_MAX__ ? __INT_MAX__ : 1 + matrix[i * p.numberOfSticks + leftIdx]);

        int topIdx = i - 1;
        int top = topIdx < 0 ? __INT_MAX__ : matrix[topIdx * p.numberOfSticks + j];

        if (left == __INT_MAX__ && left == top)
            break;

        if (left <= top)
        {
            v.push_back(p.sticks[i].first);
            j -= p.sticks[i].second;
        }

        // Si on prend un baton, on ne peut plus le choisir encore une fois.
        // Donc on doit monter pour respecter les consignes du TP
        // Exemple: Si choisi le baton numero 7, on ne peut plus le choisir
        // Donc on monte!
        i--;
    }

    free(matrix);
}
