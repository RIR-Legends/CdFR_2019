# import odrive

# Changer le step, il doit être entre le point courant le le prochain en se basant
# sur les coordonnées réelles du robot

# origine robot en bas a gauche de la table
# Angle 0 = axe Y

class Treatment:
    def __init__(self):
        self.deltaX = 0
        self.deltaY = 0
        self.deltaTheta = 0
        self.hyp = 0

    def step(self, p1, p2):
        from math import sqrt
        self.deltaX = p2['X'] - p1['X']
        self.deltaY = p2['Y'] - p1['Y']
        self.deltaTheta = p2['Theta'] - p1['Theta']

        self.hyp = sqrt(self.deltaX**2 + self.deltaY**2)

        traj_list = [self.hyp, self.deltaTheta]

        return traj_list

