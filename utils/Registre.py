# Ce fichier contient l'ensemble des points que l'on souhaite rencontrer

import time
import sys
sys.path.append('../')
from Deplacement.utils.Point_manager import Chemin


# Les points sont positionnées en coordonnées absolus*
class Creation:
    def __init__(self, cote):
        self.chemin = Chemin()
        self.cote = cote

    def main(self):
        # coté jaune
        self.chemin.add_point('aDepart', 500, 350, 90)  # le robot s'avance
        self.chemin.add_point('bPoint1', 800, 500, -90) # Le robot s'incline de l'angle nécessaire pour atteindre sa position, s'avance puis s'incline pur satisfaire l'angle final
        self.chemin.add_point('cPoint2', 400, 400, 180) 
        # self.chemin.add_point('dPoint3', 500, 500, 180)
        # self.chemin.add_point('Point4', 200, 200, 180)

        print(self.chemin.dictionnaire)



if __name__ == '__main__':
    creat = Creation(True)
    creat.main()

