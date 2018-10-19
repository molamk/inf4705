#!/usr/bin/python3

from utils import mean_duration, show_graph
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

    show_graph(algo_map)


if __name__ == '__main__':
    main()
