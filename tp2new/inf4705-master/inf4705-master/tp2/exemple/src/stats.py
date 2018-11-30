#!/usr/bin/python3

import statistics


class Result:
    algorithm = ''
    weight_order = 0
    number_order = 0
    target_weight = 0
    actual_weight = 0
    duration = 0
    exemplary = 0

    def __str__(self):
        return f'''
algorithm:\t{self.algorithm}
weight_order:\t{self.weight_order}
number_order:\t{self.number_order}
target_weight:\t{self.target_weight}
actual_weight:\t{self.actual_weight}
duration:\t{self.duration}
exemplary:\t{self.exemplary}
        '''

    def get_relative_distance(self):
        return (abs(self.target_weight - self.actual_weight) * 100) / self.target_weight

    def get_median_key(self):
        return f'{self.number_order}_{self.weight_order}_{self.exemplary}'

    def get_mean_key(self):
        return f'{self.number_order}_{self.weight_order}'


def format_file_name(filename):
    fname = filename.split('.')[0]
    parts = fname.split('-')
    if len(parts) != 4:
        parts = fname.split('_')

    return (int(parts[1]), int(parts[2]), int(parts[3]))


def format_line(line, algo):
    parts = line.split(' ')
    r = Result()

    r.algorithm = algo
    r.target_weight = int(parts[0])
    r.actual_weight = int(parts[3])
    r.duration = float(parts[2])
    r.number_order, r.weight_order, r.exemplary = format_file_name(parts[1])

    return r


def get_results_for_algo(algo):
    with open(f'../{algo}.results', 'r') as target:
        lines = target.read().split('\n')
        lines = lines[:len(lines) - 1]
        return list(map(lambda l: format_line(l, algo), lines))


def build_median_map(results):
    median_map = {}
    for r in results:
        key = r.get_median_key()
        current_arr = (r.get_relative_distance(), r.duration)

        if key not in median_map:
            median_map[key] = []

        median_map[key].append(current_arr)

    return median_map


def extract_medians(median_map):
    for k in median_map:
        deviations = []
        durations = []

        for x in median_map[k]:
            deviations.append(x[0])
            durations.append(x[1])

        median_map[k] = (statistics.median(deviations),
                         statistics.median(durations))

    return median_map


def median_key_to_mean_key(key):
    parts = key.split('_')
    return '_'.join(parts[:len(parts) - 1])


def build_mean_map(median_map):
    mean_map = {}
    for r in median_map:
        key = median_key_to_mean_key(r)
        current_arr = median_map[r]

        if key not in mean_map:
            mean_map[key] = []

        mean_map[key].append(current_arr)

    return mean_map


def generate_means(mean_map):
    for k in mean_map:
        deviations = []
        durations = []

        for x in mean_map[k]:
            deviations.append(x[0])
            durations.append(x[1])

        mean_map[k] = (round(sum(deviations) / len(deviations), 3),
                       round(sum(durations) / len(durations), 3))

    return mean_map


def format_line_width(line, width=16, filler=' '):
    l = list(str(line))
    for i in range(len(l), width):
        l.append(filler)
    return ''.join(l)


def format_block(arr):
    b = list(map(format_line_width, arr))
    return ''.join(b)


def print_result(algo, mean_map):
    print('*' * 62)
    pref = ' ' * 25
    print(f'{pref}{algo.upper()}')
    print('*' * 62)
    print(format_block(['n', 'm', 'Ecart moyen', 'Duree moyenne']))
    print('*' * 62)
    for k in mean_map:
        k_parts = k.split('_')
        dev = format_line_width(mean_map[k][0], 6, '0')
        print(format_block([k_parts[0], k_parts[1], dev, mean_map[k][1]]))
    print('\n')


if __name__ == "__main__":
    algos = ['glouton', 'progdyn1', 'progdyn2', 'recuit']

    for algo in algos:
        results = get_results_for_algo(algo)
        median_map = build_median_map(results)
        median_map = extract_medians(median_map)
        mean_map = build_mean_map(median_map)
        mean_map = generate_means(mean_map)

        print_result(algo, mean_map)
