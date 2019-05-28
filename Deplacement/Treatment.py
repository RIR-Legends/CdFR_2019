
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

        # print("Coordonnées Points: X = ", int(p[0]), " Y = ", int(p[1]), "Theta =", int(p[2]))
        
        print(p)

        self.deltaX = p[0] - self.X_abs
        self.deltaY = p[1] - self.Y_abs
        self.deltaTheta = p[2] - self.Theta_abs

        self.hyp = sqrt(self.deltaX**2 + self.deltaY**2)

        traj_list = [self.hyp, self.deltaTheta]  # [Rel, Rel]

        return traj_list

