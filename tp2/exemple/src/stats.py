#!/usr/bin/python3


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
    r.number_order, r.weight_order, r.ex = format_file_name(parts[1])

    return r


def build_algo_map(results):
    algo_map = {}
    for r in results:
        key = r.get_mean_key()
        current_arr = (r.get_relative_distance(), r.duration)

        if key not in algo_map:
            algo_map[key] = []

        algo_map[key].append(current_arr)

    return algo_map


def get_results_for_algo(algo):
    with open(f'../{algo}.results', 'r') as target:
        lines = target.read().split('\n')
        lines = lines[:len(lines) - 1]
        return list(map(lambda l: format_line(l, algo), lines))


def generate_means(algo_map):
    for k in algo_map:
        deviations = []
        durations = []

        for x in algo_map[k]:
            deviations.append(x[0])
            durations.append(x[1])

        algo_map[k] = (round(sum(deviations) / len(deviations), 3),
                       round(sum(durations) / len(durations), 3))

    return algo_map


def format_line_width(line, width=16):
    l = list(str(line))
    for i in range(len(l), width):
        l.append('0')
    return ''.join(l)


if __name__ == "__main__":
    algos = ['glouton', 'progdyn1', 'progdyn2']

    for algo in algos:
        results = get_results_for_algo(algo)

        # Median step here

        algo_map = build_algo_map(results)
        means_map = generate_means(algo_map)

        print('*' * 62)
        print(f'\t\t\t{algo.upper()}')
        print('*' * 62)
        print('n\t\tm\t\tEcart moyen\tDuree moyenne\t\t')
        print('*' * 62)
        for k in means_map:
            k_parts = k.split('_')
            dev = format_line_width(means_map[k][0], 6)
            print(
                f'{k_parts[0]}\t\t{k_parts[1]}\t\t{dev} %\t\t{means_map[k][1]}')
        print('\n')
