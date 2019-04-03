
class Point:
    def __init__(self, x, y, theta):
        self.x = x
        self.y = y
        self.theta = theta
        self.hypo = 0

        self.P = {'X': self.x, 'Y': self.y, 'theta': self.theta}

    def print_pos(self):
        print('Coordonnée en x = %f ' % self.x)
        print('Coordonnée en y = %f ' % self.y)
        print('Theta = %f ' % self.theta)

    def set_parcour(self):
        self.hypo = (self.x ** 2 + self.y ** 2) ** 0.5

    def get_point(self):
        return self.P





def main():
    point = Point()

    point.print_pos()



if __name__ == '__main__':
    main()
