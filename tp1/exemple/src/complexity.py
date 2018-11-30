#!/usr/bin/python3

from os import listdir

from utils import (mean_duration, show_graph_constant, show_graph_puissance,
                   show_graph_puissance_algo, show_graph_rapport, get_regression)


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
        if x == 'conv':
            def hypothesis(x): return x**3 / 100
            label = 'Conventionnel'
        elif x == 'strassen':
            def hypothesis(x): return x**2.8 / 1.5
            label = 'Strassen'
        else:
            def hypothesis(x): return x**2.708 / 28
            label = 'Strassen avec seuil'

        # Graphe du test de puissance
        show_graph_puissance_algo(algo_map[x], label)

        # Resultat de la regression lineaire
        print(f'{label}:\t\tPente = {get_regression(algo_map[x]).slope}')

        # Graphe du test de rapport
        show_graph_rapport(algo_map[x][1:], hypothesis, label, 1)

        # Graphe du test des constantes
        show_graph_constant(algo_map[x], hypothesis, label)


if __name__ == '__main__':
    main()
