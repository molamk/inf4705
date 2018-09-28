#!/usr/local/bin/python3

from utils import mean_duration
from os import listdir


def main():
    files = listdir('../resultats')

    for file_name in files:
        parts = file_name.split('_')
        algo = parts[0]
        size = int(parts[1].split('.')[0][len('serie')])

        moyenne = mean_duration(size, algo)
        suffix = '\t' if algo == 'conv' else ''
        print(f'Algorithme:\t{algo}{suffix}\tSize:\t{size}\tMoyenne:\t{moyenne}')


if __name__ == '__main__':
    main()
