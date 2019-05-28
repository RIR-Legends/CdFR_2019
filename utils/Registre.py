# Ce fichier contient l'ensemble des points que l'on souhaite rencontrer

from Deplacement.utils.Point_manager import Chemin


# Les points sont positionnées en coordonnées absolus*
class Creation:
    def __init__(self):
        self.chemin = Chemin()
        # self.sens = sens

    def main(self):
        # coté jaune
        self.chemin.add_point('Depart', 0, 0, 90)
        self.chemin.add_point('Point1', 100, 0, 90)
        self.chemin.add_point('Point2', 100, 100, 90)
        self.chemin.add_point('Point3', 100, 100, 180)
        self.chemin.add_point('Point4', 200, 200, 180)


        print(self.chemin.dictionnaire)

        print(self.chemin.dictionnaire['Point1'].get_point())


if __name__ == '__main__':
    creat = Creation()
    creat.main()
