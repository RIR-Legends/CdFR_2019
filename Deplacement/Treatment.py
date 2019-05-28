
# Changer le step, il doit être entre le point courant le le prochain en se basant
# sur les coordonnées réelles du robot

# origine robot en bas a gauche de la table
# Angle 90 = axe Y


class Treatment:
    def __init__(self, X_abs, Y_abs, theta): # (abs, abs, abs)
        self.X_abs = X_abs
        self.Y_abs = Y_abs
        self.Theta_abs = theta
        self.deltaX = 0
        self.deltaY = 0
        self.deltaTheta = 0
        self.hyp = 0

    def step(self, p1):
        from math import sqrt
        self.deltaX = p1['X'] - self.X_abs
        self.deltaY = p1['Y'] - self.Y_abs
        self.deltaTheta = p1['Theta'] - self.Theta_abs

        self.hyp = sqrt(self.deltaX**2 + self.deltaY**2)

        traj_list = [self.hyp, self.deltaTheta] # [Rel, Rel]

        return traj_list

