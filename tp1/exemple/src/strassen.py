#!/usr/local/bin/python3

import sys
import time

from conv import multiply_conv
from utils import print_matrix, read_matrix

ex_path1 = sys.argv[1]  # Path de la première matrice
ex_path2 = sys.argv[2]  # Path de la deuxième matrice


def add(matrix_a, matrix_b):
    rng = range(len(matrix_a))
    matrix_c = [[0 for j in rng] for i in rng]
    for i in rng:
        for j in rng:
            matrix_c[i][j] = matrix_a[i][j] + matrix_b[i][j]
    return matrix_c


def subtract(matrix_a, matrix_b):
    rng = range(len(matrix_a))
    matrix_c = [[0 for j in rng] for i in rng]
    for i in rng:
        for j in rng:
            matrix_c[i][j] = matrix_a[i][j] - matrix_b[i][j]
    return matrix_c


def strassen_recursive(matrix_a, matrix_b, threshold):
    n = len(matrix_a)

    if n <= threshold:
        return multiply_conv(matrix_a, matrix_b)
    else:
        new_size = n // 2

        rng = range(new_size)

        a11 = [[0] * new_size for i in rng]
        a12 = [[0] * new_size for i in rng]
        a21 = [[0] * new_size for i in rng]
        a22 = [[0] * new_size for i in rng]
        b11 = [[0] * new_size for i in rng]
        b12 = [[0] * new_size for i in rng]
        b21 = [[0] * new_size for i in rng]
        b22 = [[0] * new_size for i in rng]

        # dividing the matrices in 4 sub-matrices:
        for i in rng:
            for j in rng:
                a11[i][j] = matrix_a[i][j]
                a12[i][j] = matrix_a[i][j + new_size]
                a21[i][j] = matrix_a[i + new_size][j]
                a22[i][j] = matrix_a[i + new_size][j + new_size]

                b11[i][j] = matrix_b[i][j]
                b12[i][j] = matrix_b[i][j + new_size]
                b21[i][j] = matrix_b[i + new_size][j]
                b22[i][j] = matrix_b[i + new_size][j + new_size]

        p1 = strassen_recursive(add(a11, a22), add(b11, b22), threshold)
        p2 = strassen_recursive(add(a21, a22), b11, threshold)
        p3 = strassen_recursive(a11, subtract(b12, b22), threshold)
        p4 = strassen_recursive(a22, subtract(b21, b11), threshold)
        p5 = strassen_recursive(add(a11, a12), b22, threshold)
        p6 = strassen_recursive(subtract(a21, a11), add(b11, b12), threshold)
        p7 = strassen_recursive(subtract(a12, a22), add(b21, b22), threshold)

        c12 = add(p3, p5)  # c12 = p3 + p5
        c21 = add(p2, p4)  # c21 = p2 + p4
        c11 = subtract(add(add(p1, p4), p7), p5)  # c11 = p1 + p4 - p5 + p7
        c22 = subtract(add(add(p1, p3), p6), p2)  # c22 = p1 + p3 - p2 + p6

        # Grouping the results obtained in a single matrix:
        matrix_c = [[0] * n for i in range(n)]
        for i in range(0, new_size):
            for j in range(0, new_size):
                matrix_c[i][j] = c11[i][j]
                matrix_c[i][j + new_size] = c12[i][j]
                matrix_c[i + new_size][j] = c21[i][j]
                matrix_c[i + new_size][j + new_size] = c22[i][j]
        return matrix_c


def strassen(matrix_a, matrix_b, threshold=1):
    return strassen_recursive(matrix_a, matrix_b, threshold)


if __name__ == "__main__":
    a = read_matrix(ex_path1)
    b = read_matrix(ex_path2)

    start = time.time()
    matrix = strassen(a, b)
    duration = (time.time() - start) * 1000

    options = sys.argv[3:]
    if '-p' in options:  # On imprime la matrice résultat
        # Données bidon, mais output du bon format demandé
        print_matrix(matrix)
    if '-t' in options:  # On imprime le temps d'exécution
        print(duration)  # Données bidon, mais output du bon format demandé ok
