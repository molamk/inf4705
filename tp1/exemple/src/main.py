#!/usr/local/bin/python3

from utils import read_matrix
from conv import multiply_conv

file_path_1 = '../exemplaires/serie1/ex_2.5'
file_path_2 = '../exemplaires/serie1/ex_2.4'


mat_1 = read_matrix(file_path_1)
mat_2 = read_matrix(file_path_2)

mult_result = multiply_conv(mat_1, mat_2)

for line in mult_result:
    print(line)
