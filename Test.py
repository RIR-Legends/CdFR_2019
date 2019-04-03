
from point import Point

def main():

    point = Point(100, 100, 30)
    point2 = Point(200, 200, 60)

    p1 = point.get_point()
    p2 = point2.get_point()

    L = [p1, p2]

    print(L)

    print(p1['X'], p1['Y'], p1['theta'])
    print(p2['theta'])

    # L = D[1].keys()
#
    # for i in L:
    #     print(D[i])


if __name__ == '__main__':
    main()
