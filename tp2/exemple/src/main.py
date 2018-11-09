#!/usr/bin/python3

import utils


def main():
    filename = '../../jeux_de_donnees/WC-10-10-01.txt'
    lines = utils.read_lines(filename)
    batons_liste = utils.parse_batons(lines)
    print(batons_liste.nbr_batons)
    print(batons_liste.poids_limite)
    batons_liste.batons = utils.sort_tuples(batons_liste.batons)
    print(batons_liste.batons)


if __name__ == '__main__':
    main()
