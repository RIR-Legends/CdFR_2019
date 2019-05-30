
class Positionate:
    def __init__(self):
        from math import pi
        from math import cos
        from math import sin

        self.delta_pos0 = 0
        self.delta_pos1 = 0
        self.nbCounts = 8192  # Nombre de tics pr un tour d'encoder
        self.WheelDiameter = 80  # en mm
        self.WheelPerimeter = self.WheelDiameter * pi  # en mm
        self.theta_buffer = 0
        self.current_theta = 90  # en fonction du sens !
        self.current_X = 500
        self.current_Y = 0


    def step(self, pos00, pos01, pos10, pos11, theta):
        from math import pi
        from math import cos
        from math import sin

        self.theta_buffer = theta

        self.delta_pos0 = pos01 - pos00  # erreur calculée négative car moteur inversé
        self.delta_pos1 = pos11 - pos10

        self.current_theta += self.theta_buffer

        print("current_theta =", self.current_theta)

        print("delta_pos0 =", self.delta_pos0)
        print("delta_pos1 =", self.delta_pos1)

        distance0 = (- self.delta_pos0 / self.nbCounts) * self.WheelPerimeter
        distance1 = (self.delta_pos1 / self.nbCounts) * self.WheelPerimeter

        distance = (distance0 + distance1) / 2  #  Test

        print(distance)

        a = sin(self.current_theta * 2 * pi / 360)
        b = cos(self.current_theta * 2 * pi / 360)

        print("cos(theta) =", a)
        print("sin(theta) =", b)

        self.current_X += distance * a
        self.current_Y += distance * b

        print("X_ABS =", self.current_X, "Y_ABS =", self.current_Y, "Theta_abs", self.current_theta)

        return [self.current_X, self.current_Y, self.current_theta]

    def step_theta(self, theta):
        self.theta_buffer = theta

        self.current_theta += self.theta_buffer

        return self.current_theta
