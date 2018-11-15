#!/bin/bash

for algo in "glouton" "progdyn1" "progdyn2"; do
  for serie in $(ls "../jeux_de_donnees"); do
    current_filename="$algo.results"
    echo "$algo $serie"
    weight=$(tail -1 ../jeux_de_donnees/$serie)

    x=$(eval "./src/main.out -a $algo -e ../jeux_de_donnees/$serie -s -t")

    echo $x | while IFS= read -r line ; do
      echo "$weight $serie $line" >> $current_filename
    done
  done
done
