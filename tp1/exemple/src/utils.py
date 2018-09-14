def read_matrix(file_path):
    with open(file_path) as f:
        read_data = f.read()
        line = read_data.split('\n')
        matrix = list(
            map(lambda x: list(map(lambda x: int(x), x.split())), line))
        matrix = list(filter(lambda x: len(x) >= 2, matrix))
    f.closed
    return matrix
