import sys

# ex_path1 = sys.argv[1]  # Path de la première matrice
# ex_path2 = sys.argv[2]  # Path de la deuxième matrice

# TODO: Algo de multiplication de matrices ici (dans le cas de conv.py, l'algo conventionnel)


def multiply_conv(mat_1, mat_2):
    length = len(mat_1)
    result = [0] * length
    result = list(map(lambda x: [0] * length, result))

    for i in range(length):
        for j in range(length):
            for k in range(length):
                result[i][j] += mat_1[i][k]*mat_2[k][j]

    return result


# options = sys.argv[3:]
# if '-p' in options:  # On imprime la matrice résultat
#     # Données bidon, mais output du bon format demandé
#     print("2\n1\t2\t3\t4\n5\t6\t7\t8\n9\t10\t11\t12\n13\t14\t15\t16")
# if '-t' in options:  # On imprime le temps d'exécution
#     print("4.1347628746")  # Données bidon, mais output du bon format demandé ok 
