#!/usr/local/bin/python3

import sys
import time
import numpy as np

from conv import multiply_conv
from utils import print_matrix, read_matrix

ex_path1 = sys.argv[1]  # Path de la première matrice
ex_path2 = sys.argv[2]  # Path de la deuxième matrice


def add(matrix_a, matrix_b):
    return [list(map(lambda x, y: x + y, matrix_a[i], matrix_b[i])) for i in range(len(matrix_a))]


def subtract(matrix_a, matrix_b):
    return [list(map(lambda x, y: x - y, matrix_a[i], matrix_b[i])) for i in range(len(matrix_a))]


def strassen_recursive(matrix_a, matrix_b, threshold):
    total_length = len(matrix_a)
    if total_length <= threshold:
        return multiply_conv(matrix_a, matrix_b)
    else:
        half = total_length // 2
        a_11 = [[None for _ in range(half)] for __ in range(half)]
        a_12 = [[None for _ in range(half)] for __ in range(half)]
        a_21 = [[None for _ in range(half)] for __ in range(half)]
        a_22 = [[None for _ in range(half)] for __ in range(half)]
        b_11 = [[None for _ in range(half)] for __ in range(half)]
        b_12 = [[None for _ in range(half)] for __ in range(half)]
        b_21 = [[None for _ in range(half)] for __ in range(half)]
        b_22 = [[None for _ in range(half)] for __ in range(half)]

        for i in range(half):
            for j in range(half):
                a_11[i][j] = matrix_a[i][j]
                a_12[i][j] = matrix_a[i][j + half]
                a_21[i][j] = matrix_a[i + half][j]
                a_22[i][j] = matrix_a[i + half][j + half]

                b_11[i][j] = matrix_b[i][j]
                b_12[i][j] = matrix_b[i][j + half]
                b_21[i][j] = matrix_b[i + half][j]
                b_22[i][j] = matrix_b[i + half][j + half]

        m_1 = strassen_recursive(add(a_11, a_22), add(b_11, b_22), threshold)
        m_2 = strassen_recursive(add(a_21, a_22), b_11, threshold)
        m_3 = strassen_recursive(a_11, subtract(b_12, b_22), threshold)
        m_4 = strassen_recursive(a_22, subtract(b_21, b_11), threshold)
        m_5 = strassen_recursive(add(a_11, a_12), b_22, threshold)
        m_6 = strassen_recursive(subtract(a_21, a_11),
                                 add(b_11, b_12), threshold)
        m_7 = strassen_recursive(subtract(a_12, a_22),
                                 add(b_21, b_22), threshold)

        c_11 = add(subtract(add(m_1, m_4), m_5), m_7)
        c_12 = add(m_3, m_5)
        c_21 = add(m_2, m_4)
        c_22 = add(add(subtract(m_1, m_2), m_3), m_6)

        c = [[0 for x in range(total_length)] for y in range(total_length)]
        for i in range(half):
            for j in range(half):
                c[i][j] = c_11[i][j]
                c[i][j + half] = c_12[i][j]
                c[i + half][j] = c_21[i][j]
                c[i + half][j + half] = c_22[i][j]
        return c


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
