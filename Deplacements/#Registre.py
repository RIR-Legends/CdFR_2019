# Ce fichier contient l'ensemble des points que l'on souhaite rencontrer

import Deplacements.Chemin

# Les points sont positionnées en coordonnées absolus
def main():
    parcours = Deplacements.Chemin.Parcours()

    parcours.add_point('Départ', 0, 0, 0)
    parcours.add_point('Point1', 100, 0, 0)
    parcours.add_point('Point2', 100, 100, 0)
    parcours.add_point('Point3', 100, 100, 90)
    parcours.add_point('Point4', 200, 200, 90)

    print(parcours.dictionnaire)

    print(parcours.dictionnaire['Point1'].get_point())


if __name__ == '__main__':
    main()
