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
