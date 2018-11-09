from batons_liste import BatonListe, Baton


def remove_break_line(input_string):
    return input_string.split('\n')[0]


def parse_baton_line(line):
    parts = line.split('\t')
    return (int(parts[0]), int(parts[1]))


def read_lines(filename):
    with open(filename) as f:
        lines = f.readlines()
        lines = list(map(remove_break_line, lines))

        return lines


def sort_tuples(tuples_list):
    return sorted(tuples_list, key=lambda t: t[1])


def parse_batons(lines):
    batons_liste = BatonListe()

    batons_liste.nbr_batons = int(lines[0])
    batons_liste.poid_limite = int(lines[len(lines) - 1])
    batons_liste.batons = list(map(parse_baton_line, lines[1:len(lines) - 1]))

    return batons_liste
