import sys

# ex_path1 = sys.argv[1] # Path de la première matrice
# ex_path2 = sys.argv[2] # Path de la deuxième matrice

# TODO: matrix_algo de multiplication de matrices ici (dans le cas de strassen.py, l'algo de Strassen)
#!/usr/bin/python
# -*- coding: utf-8 -*-

from math import ceil, log
from conv import multiply_conv


def add(matrix_a, matrix_b):
    n = len(matrix_a)
    matrix_c = [[0 for j in range(0, n)] for i in range(0, n)]
    for i in range(0, n):
        for j in range(0, n):
            matrix_c[i][j] = matrix_a[i][j] + matrix_b[i][j]
    return matrix_c


def subtract(matrix_a, matrix_b):
    n = len(matrix_a)
    matrix_c = [[0 for j in range(0, n)] for i in range(0, n)]
    for i in range(0, n):
        for j in range(0, n):
            matrix_c[i][j] = matrix_a[i][j] - matrix_b[i][j]
    return matrix_c


def strassen_recursive(matrix_a, matrix_b, threshold):
    n = len(matrix_a)

    if n <= threshold:
        return multiply_conv(matrix_a, matrix_b)
    else:
        new_size = ceil(n/2)
        a11 = [[0 for j in range(0, new_size)] for i in range(0, new_size)]
        a12 = [[0 for j in range(0, new_size)] for i in range(0, new_size)]
        a21 = [[0 for j in range(0, new_size)] for i in range(0, new_size)]
        a22 = [[0 for j in range(0, new_size)] for i in range(0, new_size)]

        b11 = [[0 for j in range(0, new_size)] for i in range(0, new_size)]
        b12 = [[0 for j in range(0, new_size)] for i in range(0, new_size)]
        b21 = [[0 for j in range(0, new_size)] for i in range(0, new_size)]
        b22 = [[0 for j in range(0, new_size)] for i in range(0, new_size)]

        a_result = [[0 for j in range(0, new_size)]
                    for i in range(0, new_size)]
        b_result = [[0 for j in range(0, new_size)]
                    for i in range(0, new_size)]

        # dividing the matrices in 4 sub-matrices:
        for i in range(0, new_size):
            for j in range(0, new_size):
                a11[i][j] = matrix_a[i][j]            # top left
                a12[i][j] = matrix_a[i][j + new_size]    # top right
                a21[i][j] = matrix_a[i + new_size][j]    # bottom left
                a22[i][j] = matrix_a[i + new_size][j + new_size]  # bottom right

                b11[i][j] = matrix_b[i][j]            # top left
                b12[i][j] = matrix_b[i][j + new_size]    # top right
                b21[i][j] = matrix_b[i + new_size][j]    # bottom left
                b22[i][j] = matrix_b[i + new_size][j + new_size]  # bottom right

        # matrix_calculating p1 to p7:
        a_result = add(a11, a22)
        b_result = add(b11, b22)
        # p1 = (a11+a22) * (b11+b22)
        p1 = strassen_recursive(a_result, b_result, threshold)

        a_result = add(a21, a22)      # a21 + a22
        p2 = strassen_recursive(a_result, b11, threshold)  # p2 = (a21+a22) * (b11)

        b_result = subtract(b12, b22)  # b12 - b22
        p3 = strassen_recursive(a11, b_result, threshold)  # p3 = (a11) * (b12 - b22)

        b_result = subtract(b21, b11)  # b21 - b11
        p4 = strassen_recursive(a22, b_result, threshold)   # p4 = (a22) * (b21 - b11)

        a_result = add(a11, a12)      # a11 + a12
        p5 = strassen_recursive(a_result, b22, threshold)  # p5 = (a11+a12) * (b22)

        a_result = subtract(a21, a11)  # a21 - a11
        b_result = add(b11, b12)      # b11 + b12
        # p6 = (a21-a11) * (b11+b12)
        p6 = strassen_recursive(a_result, b_result, threshold)

        a_result = subtract(a12, a22)  # a12 - a22
        b_result = add(b21, b22)      # b21 + b22
        # p7 = (a12-a22) * (b21+b22)
        p7 = strassen_recursive(a_result, b_result, threshold)

        # calculating c21, c21, c11 e c22:
        c12 = add(p3, p5)  # c12 = p3 + p5
        c21 = add(p2, p4)  # c21 = p2 + p4

        a_result = add(p1, p4)  # p1 + p4
        b_result = add(a_result, p7)  # p1 + p4 + p7
        c11 = subtract(b_result, p5)  # c11 = p1 + p4 - p5 + p7

        a_result = add(p1, p3)  # p1 + p3
        b_result = add(a_result, p6)  # p1 + p3 + p6
        c22 = subtract(b_result, p2)  # c22 = p1 + p3 - p2 + p6

        # Grouping the results obtained in a single matrix:
        matrix_c = [[0 for j in range(0, n)] for i in range(0, n)]
        for i in range(0, new_size):
            for j in range(0, new_size):
                matrix_c[i][j] = c11[i][j]
                matrix_c[i][j + new_size] = c12[i][j]
                matrix_c[i + new_size][j] = c21[i][j]
                matrix_c[i + new_size][j + new_size] = c22[i][j]
        return matrix_c


def strassen(matrix_a, matrix_b, threshold=1):
    assert type(matrix_a) == list and type(matrix_b) == list
    assert len(matrix_a) == len(matrix_a[0]) == len(
        matrix_b) == len(matrix_b[0])

    # Make the matrices bigger so that you can apply the strassen
    # algorithm recursively without having to deal with odd
    # matrix sizes
    def nextPowerOfTwo(n): return 2**int(ceil(log(n, 2)))
    n = len(matrix_a)
    m = nextPowerOfTwo(n)
    a_prep = [[0 for i in range(m)] for j in range(m)]
    b_prep = [[0 for i in range(m)] for j in range(m)]
    for i in range(n):
        for j in range(n):
            a_prep[i][j] = matrix_a[i][j]
            b_prep[i][j] = matrix_b[i][j]
    c_prep = strassen_recursive(a_prep, b_prep, threshold)
    c_matrix = [[0 for i in range(n)] for j in range(n)]
    for i in range(n):
        for j in range(n):
            c_matrix[i][j] = c_prep[i][j]
    return c_matrix

# options = sys.argv[3:]
# if '-p' in options: # On imprime la matrice résultat
#     print("2\n1\t2\t3\t4\n5\t6\t7\t8\n9\t10\t11\t12\n13\t14\t15\t16") # Données bidon, mais output du bon format demandé
# if '-t' in options: # On imprime le temps d'exécution
#     print("4.1347628746") # Données bidon, mais output du bon format demandé
