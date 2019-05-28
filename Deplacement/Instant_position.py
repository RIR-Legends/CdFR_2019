from math import pi
from math import cos
from math import sin


class Positionate:
    def __init__(self, pos00, pos01, pos10, pos11, theta):
        self.delta_pos0 = pos01 - pos00
        self.delta_pos1 = pos11 - pos10
        self.nbCounts = 8192  # Nombre de tics pr un tour d'encoder
        self.WheelDiameter = 80  # en mm
        self.WheelPerimeter = self.WheelDiameter * pi  # en mm
        self.theta_buffer = theta
        self.current_theta = 90  # en fonction du sens !
        self.current_X = 500
        self.current_Y = 0



    def step(self):

        self.current_theta += self.theta_buffer

        print("current_theta =", self.current_theta)

        distance0 = (self.delta_pos0 * self.WheelPerimeter) / self.nbCounts
        distance1 = (self.delta_pos1 * self.WheelPerimeter) / self.nbCounts

        distance = (distance0 + distance1) / 2

        print(distance)

        self.current_X += distance * cos(self.current_theta)
        self.current_Y += distance * sin(self.current_theta)

        return [self.current_X, self.current_Y, self.current_theta]
