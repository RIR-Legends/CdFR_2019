# -*- coding: utf-8 -*-

from Deplacements.point import Point


class Chemin:
    def __init__(self):
        self.Point = Point
        self.dictionnaire = dict()
        #  définir les dictionnaire où l'on ira chercher les points

    def add_point(self, name, x, y, theta):          #  ajoute au dico des points un nouveau point, où tu peux acceder a ses coordonnées par sa clés qui est "name"
        self.dictionnaire[name] = self.Point(x, y, theta)

    def modif_point(self, name, x2, y2, theta2):  # remplace les coordonnées d'un point par de nouvelles
        self.dictionnaire[name] = self.Point(x2, y2, theta2)

    def delete_point(self, name):  # supprime un point a partir de son nom
        self.dictionnaire.pop(name, None)

    # def add_point(self, namePoint, x, y, theta):
    # valuePoint = self.Point()
    # # pour creer un nouveau point contenant les coordonnées rentrées en arg.
    # print('Point %f créé : ' % x) # affiche ce point avec ces coordonnées.

    # def modify_point(self, namePoint):
    # # demande de saisir la cle à modifier
    # print('Dans le point %f : \n' % namePoint )
    # keyWas = input("Quelle coordonnée veux tu modifier ? (x ou y ou theta)"")
    # # affiche la clé et sa valeur actuelle
    # print('La coordonnée %f actuelle vaut : %f ' % keyWas % self.namePoint[keyWas])
    # # demande la nouvelle valeur de la clé
    # keyIs = input("Par qelle valeur veux tu la remplacer ?")
    # print("Le point %f vaut maintenant : %f" % namePoint % self.namePoint)

    # def suppress_point(self, namePoint):
    # YorN = input('Tu souhaite supprimer le point %f ? (Y ou N)', % namePoint)
    # if YorN == 'Y':
    #     # Suppression du Point
    #     del self.namePoint  # pas sur du résultat /!\
    #     print('Le point %f a été supprimé.' % namePoint)
    # elif YorN == 'N':
    #     # Ne supprime pas le Point
    #     print('Le point n\'a pas été supprimé.')
    # else:
    #     # Erreur d'entrée
    #     print('Seul Y et N sont accéptés !')


def main():
    Class = Chemin()
    Class.add_point('Point1', 100, 200, 60)
    Class.add_point('Point2', 500, 300, 90)

    P1 = Class.dictionnaire['Point1'].get_point()
    P2 = Class.dictionnaire['Point2'].get_point()
    print("P1 =", P1)
    print("P2 =", P2)

    Class.modif_point('Point2', 500, 350, 90)

    P2 = Class.dictionnaire['Point2'].get_point()

    print("\nP1 =", P1)
    print("P2 =", P2)

    Class.delete_point('Point2')

    print(Class.dictionnaire.keys())

if __name__ == '__main__':
    main()






