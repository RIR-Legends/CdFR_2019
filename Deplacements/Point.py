
class Point:
    def __init__(self):
        self.x = 4120000
        self.y = 0
        self.theta = 0
        self.hypo = 0

    def print_pos(self):
        print('Coordonnée en x = %f ' % self.x)
        print('Coordonnée en y = %f ' % self.y)
        print('Theta = %f ' % self.theta)

    def set_parcour(self):
        self.hypo = (self.x ** 2 + self.y ** 2) ** 0.5




def main():
    point = Point()

    point.print_pos()



if __name__ == '__main__':
    main()
