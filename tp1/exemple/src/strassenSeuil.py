#!/usr/bin/python3

import sys
import time
import math

from strassen import strassen
from utils import print_matrix, read_matrix

ex_path1 = sys.argv[1]  # Path de la première matrice
ex_path2 = sys.argv[2]  # Path de la deuxième matrice


def strassen_seuil(matrix_a, matrix_b, seuil):
    return strassen(matrix_a, matrix_b, seuil)


ex_path1 = sys.argv[1]  # Path de la première matrice
ex_path2 = sys.argv[2]  # Path de la deuxième matrice


def looper(a, b, seuil):
    start = time.time()
    _ = strassen_seuil(a, b, seuil)
    duration = (time.time() - start) * 1000
    print(f'{seuil}\t{duration}')


if __name__ == "__main__":
    a = read_matrix(ex_path1)
    b = read_matrix(ex_path2)

    # seuil = 150

    # seuil = len(a) // 2

    for seuil in range(len(a), len(a) // 3, -len(a) // 10):
        looper(a, b, seuil)

    # start = time.time()
    # matrix = strassen_seuil(a, b)
    # duration = (time.time() - start) * 1000

    # options = sys.argv[3:]
    # if '-p' in options:  # On imprime la matrice résultat
    #     # Données bidon, mais output du bon format demandé
    #     print_matrix(matrix)
    # if '-t' in options:  # On imprime le temps d'exécution
    #     print(duration)  # Données bidon, mais output du bon format demandé ok
