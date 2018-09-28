import statistics


def read_matrix(file_path):
    with open(f'./exemplaires/{file_path}') as f:
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
