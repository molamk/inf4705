#!/usr/local/bin/python3

from utils import read_matrix, print_matrix
from conv import multiply_conv
from strassen import strassen

file_path_1 = '../exemplaires/serie1/ex_2.5'
file_path_2 = '../exemplaires/serie1/ex_2.4'


mat_1 = read_matrix(file_path_1)
mat_2 = read_matrix(file_path_2)

mult_result_conv = multiply_conv(mat_1, mat_2)
mult_result_strassen = strassen(mat_1, mat_2)

seuil = 2

mult_result_strassen_seuil = strassen(mat_1, mat_2, seuil)

print_matrix(mult_result_conv)
print('*' * 100)
print_matrix(mult_result_strassen)
print('*' * 100)
print_matrix(mult_result_strassen_seuil)
