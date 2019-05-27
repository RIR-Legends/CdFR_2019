# stratégie d'évitement, input : valeur entre 0 et 255 sur la proximité de l'obstacle (255 = au+proche)

from Deplacements.chemin import Chemin
from Deplacements.move import Move
from Deplacements.point import Point


class Evitement:
    def __init__(self, p1, p2):
        self.parcours = Chemin()
        self.move = Move(p1, p2)
        self.point = self.move.current_point
        self.threshold = 200
        self.direction = None
        pass

    def evitement(self, direction):

        self.direction = direction

        if self.direction == 'droite':
            self.parcours.add_point('PointEv1', self.move.current_point.X, self.move.current_point.Y, self.move.current_point.Theta)

        elif self.direction == 'gauche':
            pass

        else:  # self.sens == 'arriere'
            pass

