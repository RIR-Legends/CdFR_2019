# Ce fichier contient l'ensemble des points que l'on souhaite rencontrer

import Deplacements.chemin


# Les points sont positionnées en coordonnées absolus*
class Creation:
    def __init__(self):
        self.chemin = Deplacements.chemin.Chemin()

    def main(self):
        self.chemin.add_point('Depart', 0, 0, 0)
        self.chemin.add_point('Point1', 100, 0, 0)
        self.chemin.add_point('Point2', 100, 100, 0)
        self.chemin.add_point('Point3', 100, 100, 90)
        self.chemin.add_point('Point4', 200, 200, 90)


        print(self.chemin.dictionnaire)

        print(self.chemin.dictionnaire['Point1'].get_point())


if __name__ == '__main__':
    creat = Creation()
    creat.main()
