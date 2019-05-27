import Deplacements.chemin
import Deplacements.point
import Deplacements.Treatment
import Deplacements.Evitement
import Deplacements.Test
import Deplacements.Registre


def main():
    # creation du dico avec les valeurs des points
    creation = Deplacements.Registre.Creation()
    creation.main()
    # fin

    # récupération des valeurs des points
    Registre_points = Deplacements.Test.Recuperation(creation.chemin.dictionnaire)
    # fin

    #
    Treatment

    # déplacements

    Evitement
    # déplacements




if __name__ == "__main__":
    main()