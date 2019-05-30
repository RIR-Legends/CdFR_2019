# -*- coding: utf-8 -*-

from collections import OrderedDict
from ast import literal_eval

class Point:
    def __init__(self, *args):
        if len(args) == 1: # Considère un tuple (x,y,theta)
            self.x, self.y, self.theta = args[0][0], args[0][1], args[0][2]
        elif len(args) == 3: # Considère trois float x,y,theta
            self.x, self.y, self.theta = args[0], args[1], args[2]
        #self.hypo = 0

        #self.d1_buffer = {'X': self.x, 'Y': self.y, 'ztheta': self.theta}
        #self.P = OrderedDict(sorted(self.d1_buffer.items(), key=lambda t: t[0]))


    def print_pos(self):
        print('Coordonnée en x = %f ' % self.x)
        print('Coordonnée en y = %f ' % self.y)
        print('Theta = %f ' % self.theta)

    #def set_parcour(self):
    #    self.hypo = (self.x ** 2 + self.y ** 2) ** 0.5

    def get_point(self):
        return (self.x, self.y, self.theta)
    
    def get_db_point(name, db):
        '''
        name : Nom du point
        db : Nom du fichier de donnée, chemin relatif vers le fichier
        '''
        
        return Point(literal_eval(db.get(name)))
    
    def mirror(self):
        self.y = 3000 - self.y
        self.theta = 180 - self.theta # Valeur positive et négative


def main():
    p = Point(100, 200, 90)

    print(p.d1_buffer)

    print(p.P)


if __name__ == '__main__':
    main()



### EXEMPLE AVEC BASE DE DONNEE
#import filedb
#from point import Point
#from ast import literal_eval
#
#db = filedb.fileDB(db="../Points")
#db.set("PointZero",Point(0,0,0).get_point())
#
#data = literal_eval(db.get("PointZero"))
#
#p = Point(data[0],data[1],data[2])
#p.print_pos()
### FIN EXEMPLE