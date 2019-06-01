
# Changer le step, il doit être entre le point courant le le prochain en se basant
# sur les coordonnées réelles du robot

# origine robot en bas a gauche de la table
# Angle 90 = axe Y


class Treatment:
    def __init__(self, x_abs, y_abs, theta_abs):  # (abs, abs, abs)
        self.X_abs = x_abs
        self.Y_abs = y_abs
        self.Theta_abs = theta_abs
        self.deltaX = 0
        self.deltaY = 0

        self.deltaTheta_intra = 0
        self.deltaTheta_rotreal = 0
        self.hyp = 0

    def step(self, p):
        from math import sqrt
        from math import atan
        from math import pi
        from numpy import sign

        print(p)

        print("Coordonnées Points Absolu : X_ABS = %f , Y_ABS = %f , Theta_ABS = %f " % (
            self.X_abs, self.Y_abs, self.Theta_abs))

        print("Coordonnées Points: X = %f , Y = %f , Theta = %f " % (p[0], p[1], p[2]))

        self.deltaX = p[0] - self.X_abs  # avec la base de donnée on a p.x
        self.deltaY = p[1] - self.Y_abs  # avec la base de donnée on a p.y

        self.hyp = sqrt(self.deltaX**2 + self.deltaY**2)

        # Gestion cas pariculier pas de DeltaX
        if self.deltaX == 0:
            if self.deltaTheta_intra > 0:  # self.deltaY
                self.deltaTheta_rotreal = 90 - self.Theta_abs
            elif self.deltaTheta_intra < 0:  # self.deltaY
                self.deltaTheta_rotreal = -90 - self.Theta_abs
        else:
        # Gestion cas particulier Arctan
            if self.deltaY > 0 > self.deltaX:
                self.deltaTheta_intra = ((atan(self.deltaY/self.deltaX) + pi) * 180) / pi
            elif self.deltaY < 0 and self.deltaX < 0:
                self.deltaTheta_intra = ((atan(self.deltaY / self.deltaX) - pi) * 180) / pi
            else:
                self.deltaTheta_intra = (atan(self.deltaY/self.deltaX) * 180) / pi

        # Gestion cas pariculier pas de DeltaY
            if self.deltaTheta_intra == 0:
                self.deltaTheta_rotreal = 0
            else:
                self.deltaTheta_rotreal = self.deltaTheta_intra - self.Theta_abs

        if sign(self.deltaX) < 0:
            self.deltaTheta_rotreal -= pi
        elif sign(self.deltaY) < 0:
            self.deltaTheta_rotreal += pi

        traj_list = [self.hyp, self.deltaTheta_rotreal]  # [Rel, Rel]

        return traj_list
