#!/usr/local/bin/python3

import sys
import time

from utils import print_matrix, read_matrix

ex_path1 = sys.argv[1]  # Path de la première matrice
ex_path2 = sys.argv[2]  # Path de la deuxième matrice


def multiply_conv(mat_1, mat_2):
    length = len(mat_1)
    result = [0] * length
    result = list(map(lambda x: [0] * length, result))

    for i in range(length):
        for j in range(length):
            for k in range(length):
                result[i][j] += mat_1[i][k]*mat_2[k][j]

    return result


if __name__ == "__main__":
    a = read_matrix(ex_path1)
    b = read_matrix(ex_path2)

    start = time.time()
    matrix = multiply_conv(a, b)
    duration = (time.time() - start) * 1000

    options = sys.argv[3:]
    if '-p' in options:  # On imprime la matrice résultat
        # Données bidon, mais output du bon format demandé
        print_matrix(matrix)
    if '-t' in options:  # On imprime le temps d'exécution
        print(duration)  # Données bidon, mais output du bon format demandé ok
