# Import librairies externes
from __future__ import print_function
import odrive

# Import programme Robot
from Deplacement.Treatment import Treatment
from Deplacement.Dodging import Dodging
from Deplacement.utils.Recovery import Recuperation
from utils.Registre import Creation
from Deplacement.Movement.move import Move
from Deplacement.Instant_position import Positionate


from odrive.enums import *



def main():

    # initialisation
    X_abs = 0
    Y_abs = 0
    Theta_abs = 0


    # Recherche des Odrive
    odrv0 = odrive.find_any()

    # creation du dico avec les valeurs des points
    creation = Creation()
    creation.main()
    # fin

    # récupération des valeurs des points
    Registre_points = Recuperation(creation.chemin.dictionnaire)
    # fin

# for P in range(len(Registre_points)):

    # Traitement
    treatment = Treatment(X_abs, Y_abs, Theta_abs)
    Traj_list = treatment.step(P) # Traj_list = [ Distance, Theta ]
    # fin


    # déplacements
    move = Move(odrv0)

        # Rotation
    move.rotation(Traj_list[2])
        # fin

            # Recuperation de position instant 1er composante
    pos00 = odrv0.axis0.encoder.pos_estimate
    pos10 = odrv0.axis1.encoder.pos_estimate
            # fin

        # Translation
    move.translation(Traj_list[1])
        # fin


            # Recuperation de position instant 2eme composantes
    pos01 = odrv0.axis0.encoder.pos_estimate
    pos11 = odrv0.axis1.encoder.pos_estimate
            # fin

    # fin

    # instant position
    positionate = Positionate(pos00, pos01, pos10, pos11, Traj_list[2])
    [X_abs, Y_abs, Theta_abs] = positionate.step()
    # fin


    # evitement
    dodging = Dodging() # TODO : Coder dodging
    # fin


if __name__ == "__main__":
    main()