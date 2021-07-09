import names
from random import randint

FILE_SIZE = 50


def get_random_bd() -> str:
    return "{:02d}.".format(randint(0, 28)) + \
           "{:02d}.".format(randint(1, 12)) + \
           "{:04d}".format(randint(1950, 2021))


class Record:
    def __init__(self, name, birthday):
        self.name = name
        self.birthday = birthday


def main():
    filenames = ['student_file_1.txt', 'student_file_2.txt']

    with open(filenames[0], 'a') as f:
        for i in range(FILE_SIZE):
            temp = Record(names.get_full_name(), get_random_bd())
            f.write('{:d} {} {}\n'.format(i + 1, temp.name, temp.birthday))

    with open(filenames[1], 'a') as f:
        for i in range(FILE_SIZE):
            temp = Record(names.get_full_name(), get_random_bd())
            f.write('{:d} {} {}\n'.format(i + 1, temp.name, temp.birthday))


if __name__ == '__main__':
    main()
