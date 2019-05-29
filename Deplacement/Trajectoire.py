#!/usr/bin/env python3

# Import librairies externes
from __future__ import print_function
import odrive
import sys

# Import programme Robot
from Treatment import Treatment
from utils.Recovery import Recuperation
sys.path.append('Movement/')
from Movement.move import Move
from Instant_position import Positionate
from Movement.param import Param
# from Dodging import Dodging


sys.path.append('../')

from utils.Registre import Creation
import utils.Switch as Switch


def main():

    # initialisation des Odrives
    param = Param()
    param.config()
    param.calib()
    print("fin de de calibration")

    # initialisation des paramètres ABS
    X_abs = 500  # appel programme de mise en place init
    Y_abs = 0  # appel porgramme de mise en place init
    Theta_abs = 90
    print("position init abs : X = %f, Y = %f, Theta = %f" % (X_abs, Y_abs, Theta_abs))

    # Récupération de la carte Odrive
    odrv0 = param.odrv0

    # récuperation cote + tirette
    cote = Switch.cote()  # Jaune = True, Violet = False

    # creation du dico avec les valeurs des points
    creation = Creation(cote)  # bool de l'interrupteur tirrette TODO : Prise en compte du coté dans Registre
    creation.main()
    # fin

    # récupération des valeurs des points
    recuperation = Recuperation(creation.chemin.dictionnaire)
    Registre_points = recuperation.main()
    print(Registre_points)
    # fin
    
    # Boucle Bloquante Tirette
    Switch.tirette()

    # initialisation des classes
    positionate = Positionate()

    for P in Registre_points:  # TODO : implementer la boucle for pour le déroulement de l'itinéraire

        # Traitement
        treatment = Treatment(X_abs, Y_abs, Theta_abs)
        Traj_list = treatment.step(P)  # Traj_list = [ Distance, Theta ]
        print("Traj_list = %s" % Traj_list)
        # fin


        # déplacements
        move = Move(odrv0)

            # Rotation
        if Traj_list[1] != 0:   # Theta != 0
            Senslist = [True, True, True, True, True]
            move.rotation(Traj_list[1], Senslist)
            # fin

                # Recuperation de position instant 1er composante
        pos00 = odrv0.axis0.encoder.pos_estimate
        pos10 = odrv0.axis1.encoder.pos_estimate
        print("pos 00 = ", pos00)
        print("pos 10 = ", pos10)
                # fin

            # Translation
        Senslist = [0, 0, 0, 0, 0]
        if Traj_list[0] != 0:   # Distance != 0
            if Traj_list[0] >= 0:
                Senslist = [True, True, True, False, False]

            elif Traj_list[0] < 0:
                Senslist = [False, False, False, True, True]

            move.translation(Traj_list[0], Senslist)
            # fin

                # retour capteur collision
        print("liste des capteurs actifs", move.SenOn)

                # Recuperation de position instant 2eme composantes
        pos01 = odrv0.axis0.encoder.pos_estimate
        pos11 = odrv0.axis1.encoder.pos_estimate
        print("pos 01 = ", pos01)
        print("pos 11 = ", pos11)
                # fin

        # fin

        # instant position
        [X_abs, Y_abs, Theta_abs] = positionate.step(pos00, pos01, pos10, pos11, Traj_list[1])
        print("position abs : X = %f, Y = %f, Theta = %f" % (X_abs, Y_abs, Theta_abs))
        # fin

        print("dodging begin")

        # evitement
        # dodging = Dodging() # TODO : Coder dodging
        # fin

        print("dodging end")

if __name__ == "__main__":
    main()
