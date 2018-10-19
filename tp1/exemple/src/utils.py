import statistics
import matplotlib
import matplotlib.pyplot as plt
import numpy as np


def read_matrix(file_path):
    with open(f'../exemplaires/{file_path}') as f:
        read_data = f.read()
        line = read_data.split('\n')
        matrix = list(
            map(lambda x: list(map(lambda x: int(x), x.split())), line))
        matrix = list(filter(lambda x: len(x) >= 2, matrix))
    f.closed
    return matrix


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


def show_graph(algo_map):
    y1 = np.array(algo_map['conv'])
    y2 = np.array(algo_map['strassen'])
    y3 = np.array(algo_map['strassenSeuil'])
    s = np.arange(1, len(y1) + 1, 1)

    _, ax = plt.subplots()
    ax.set_xscale('log')
    ax.set_yscale('log')

    ax.plot(s, y1, label='Conventionnel')
    ax.plot(s, y2, label='Strassen')
    ax.plot(s, y3, label='Strassen avec seuil')

    ax.set(xlabel='Taille 2^n', ylabel='Temps d\'execution (ms)',
           title='Temps d\'exection en fonction des tailles')
    ax.grid()

    plt.legend(loc='best')
    plt.show()
