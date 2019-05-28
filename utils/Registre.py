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
        self.chemin.add_point('aDepart', 500, 100, 90)
        self.chemin.add_point('bPoint1', 500, 1500, 90)
        self.chemin.add_point('cPoint2', 500, 500, -90)
        self.chemin.add_point('dPoint3', 500, 500, 180)
        # self.chemin.add_point('Point4', 200, 200, 180)

        print(self.chemin.dictionnaire)



if __name__ == '__main__':
    creat = Creation(True)
    creat.main()

