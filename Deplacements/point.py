# -*- coding: utf-8 -*-

class Point:
    def __init__(self, x, y, theta):
        self.x = x
        self.y = y
        self.theta = theta
        self.hypo = 0

        self.P = {'X': self.x, 'Y': self.y, 'theta': self.theta}

    def print_pos(self):
        print('Coordonnée en x = %f ' % self.x)
        print('Coordonnée en y = %f ' % self.y)
        print('Theta = %f ' % self.theta)

    def set_parcour(self, ):
        self.hypo = (self.x ** 2 + self.y ** 2) ** 0.5

    def get_point(self):
        return self.P


    def add_point(self, namePoint, x, y, theta):

        self.namePoint = {'X': self.x, 'Y': self.y, 'theta': self.theta}
        # pour creer un nouveau point contenant les coordonnées rentrées en arg.
        print('Point %f créé : ' % x) # affiche ce point avec ces coordonnées.

    def modify_point(self, namePoint):
        # demande de saisir la cle à modifier
        print('Dans le point %f : \n' % namePoint )
        keyWas = input("Quelle coordonnée veux tu modifier ? (x ou y ou theta)")
        # affiche la clé et sa valeur actuelle
        print('La coordonnée %f actuelle vaut : %f ' % keyWas % self.namePoint[keyWas])
        # demande la nouvelle valeur de la clé
        keyIs = input("Par qelle valeur veux tu la remplacer ?")
        print("Le point %f vaut maintenant : %f" % namePoint % self.namePoint)

    def suppress_point(self, namePoint):
        YorN = input('Tu souhaite supprimer le point %f ? (Y ou N)' % namePoint)
        if YorN == 'Y':
            #Suppression du Point
            del self.namePoint #pas sur du résultat /!\
            print('Le point %f a été supprimé.' % namePoint)
        elif YorN == 'N':
            #Ne supprime pas le Point
            print('Le point n\'a pas été supprimé.')
        else:
            #Erreur d'entrée
            print('Seul Y et N sont accéptés !')

def main():
    point = Point()

    point.print_pos()



if __name__ == '__main__':
    main()
