# Ce fichier contient l'ensemble des points que l'on souhaite rencontrer

from point import Point


class Chemin:
    def __init__(self):
        self.Point = Point
        self.D = dict()
        #  définir les dictionnaire où l'on ira chercher les points


    # def add(self, name, x, y, theta):          #  ajoute au dico des points un nouveau point, où tu peux acceder a ses coordonnées par sa clés qui est "name"
    #     #     self.D[name] = self.Point(x, y, theta).get_point()
    #
    #     # def modif_point(self):

