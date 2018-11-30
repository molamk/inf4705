#!/usr/bin/python3

from utils import mean_duration, show_graph_puissance, show_graph_puissance_algo, show_graph_rapport
from os import listdir


def main():
    files = listdir('../resultats')
    algo_map = {}

    for file_name in files:
        parts = file_name.split('_')
        algo = parts[0]
        size = int(parts[1].split('.')[0][len('serie')])

        moyenne = mean_duration(size, algo)

        if algo in algo_map:
            algo_map[algo].append(moyenne)
        else:
            algo_map[algo] = [moyenne]

    for x in algo_map:
        algo_map[x].sort()

        # print(x)
        # #algo_map[x] = list(map(lambda x: x * 1000, algo_map[x]))
        # print(algo_map[x])
        # print()

    # show_graph_puissance(algo_map)
    show_graph_puissance_algo(algo_map['conv'], 'Conventionnel')

    # def hypothesis(x): return x**3
    # show_graph_rapport(algo_map['strassenSeuil'], hypothesis, 'strassenSeuil')


if __name__ == '__main__':
    main()
