import statistics
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from scipy import stats
import math


def read_matrix(file_path):
    with open(f'./exemplaires/{file_path}') as f:
        read_data = f.read()
        line = read_data.split('\n')
        matrix = list(
            map(lambda x: list(map(lambda x: int(x), x.split())), line))
        matrix = list(filter(lambda x: len(x) >= 2, matrix))
    f.closed
    m = np.zeros((len(matrix), len(matrix)))
    for i in range(len(matrix)):
        for j in range(len(matrix)):
            m[i][j] = matrix[i][j]
    return m


def print_matrix(matrix):
    print(len(matrix))
    for line in matrix:
        str_line = '\t'.join([str(x) for x in line])
        print(str_line)


# in milliseconds
def read_durations(size, algo):
    durations_list = []

    file_path = format_duration_file_name(size, algo)
    with open(f'../resultats/{file_path}') as f:
        read_data = f.read()
        lines = read_data.split('\n')
        lines = list(filter(lambda x: len(x) > 0, lines))
        for line in lines:
            duration = float(line) * 1000
            durations_list.append(duration)
    f.closed
    return durations_list


def format_duration_file_name(size, algo):
    return f'{algo}_serie{size}.csv'


def mean_duration(size, algo):
    return statistics.mean(read_durations(size, algo))


def show_graph_puissance(algo_map):
    y1 = np.array(algo_map['conv'])
    y2 = np.array(algo_map['strassen'])
    y3 = np.array(algo_map['strassenSeuil'])
    s = np.arange(1, len(y1) + 1, 1)
    s = list(map(lambda x: 2 ** x, s))

    print(get_regression(y1))
    print(get_regression(y2))
    print(get_regression(y3))

    _, ax = plt.subplots()
    ax.set_xscale('log')
    ax.set_yscale('log')

    ax.plot(s, y1, label='Conventionnel', color='blue')
    ax.plot(s, y2, label='Strassen', color='red')
    ax.plot(s, y3, label='Strassen avec seuil', color='black')

    ax.set(xlabel='Taille 2^n', ylabel='Temps d\'execution (ms)',
           title='Temps d\'exection en fonction des tailles')
    ax.grid()

    plt.legend(loc='best')
    plt.show()


def show_graph_puissance_algo(data, algo):
    y = np.array(data)
    s = np.arange(1, len(y) + 1, 1)
    s = list(map(lambda x: 2 ** x, s))

    _, ax = plt.subplots()
    ax.set_xscale('log')
    ax.set_yscale('log')

    ax.plot(s, y, label=algo, color='blue')

    ax.set(xlabel='Taille 2^n', ylabel='Temps d\'execution (ms)',
           title=f'Temps d\'execution de l\'algorithme {algo} en fonction des tailles')
    ax.grid()

    plt.legend(loc='best')
    plt.show()


def show_graph_rapport(data, hypothesis, algo):
    y = np.array(data)
    s = np.arange(1, len(y) + 1, 1)
    hyp = [None] * len(data)

    for i in range(len(y)):
        hyp[i] = y[i] / hypothesis(2**(i + 1))

    # print(s)
    # print(hyp)

    _, ax = plt.subplots()

    ax.plot(s, hyp, label='algo', color='red')

    ax.set(xlabel='Taille 2^n', ylabel='Temps d\'execution (ms)',
           title=f'Temps d\'exection de {algo} en fonction des tailles')
    ax.grid()

    plt.legend(loc='best')
    plt.show()


def get_regression(data):
    s = np.arange(1, len(data) + 1, 1)
    s = list(map(lambda x: math.log(2**x), list(s)))

    data = list(map(lambda x: math.log(x), list(data)))
    return stats.linregress(s, data)
