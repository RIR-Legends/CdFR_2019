
# Changer le step, il doit être entre le point courant le le prochain en se basant
# sur les coordonnées réelles du robot

# origine robot en bas a gauche de la table
# Angle 90 = axe Y


class Treatment:
    def __init__(self, X_abs, Y_abs, Theta_abs):  # (abs, abs, abs)
        self.X_abs = X_abs
        self.Y_abs = Y_abs
        self.Theta_abs = Theta_abs
        self.deltaX = 0
        self.deltaY = 0
        self.deltaTheta = 0
        self.hyp = 0

    def step(self, p):
        from math import sqrt

        print(p)

        print("Coordonnées Points: X = %f , Y = %f , Theta = %f " % (p[0], p[1], p[2]))

        self.deltaX = p[0] - self.X_abs
        self.deltaY = p[1] - self.Y_abs
        self.deltaTheta = p[2] - self.Theta_abs

        if self.deltaTheta > 180 or self.deltaTheta < -180:
            if self.deltaTheta > 0:
                self.deltaTheta -= 360
            elif self.deltaTheta < 0:
                self.deltaTheta += 360

        self.hyp = sqrt(self.deltaX**2 + self.deltaY**2)

        traj_list = [self.hyp, self.deltaTheta]  # [Rel, Rel]

        return traj_list

