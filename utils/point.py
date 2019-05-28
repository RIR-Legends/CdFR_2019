# -*- coding: utf-8 -*-

from collections import OrderedDict


class Point:
    def __init__(self, x, y, theta):
        self.x = x
        self.y = y
        self.theta = theta
        self.hypo = 0

        self.d1_buffer = {'X': self.x, 'Y': self.y, 'ztheta': self.theta}
        self.P = OrderedDict(sorted(self.d1_buffer.items(), key=lambda t: t[0]))


    def print_pos(self):
        print('Coordonnée en x = %f ' % self.x)
        print('Coordonnée en y = %f ' % self.y)
        print('Theta = %f ' % self.theta)

    def set_parcour(self):
        self.hypo = (self.x ** 2 + self.y ** 2) ** 0.5

    def get_point(self):
        return (self.x, self.y, self.theta)


def main():
    p = Point(100, 200, 90)

    print(p.d1_buffer)

    print(p.P)


if __name__ == '__main__':
    main()
