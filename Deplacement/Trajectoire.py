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
import utils.Switch as switch



def main():

    # initialisation des paramètres ABS
    X_abs = 500  # appel programme de mise en place init
    Y_abs = 0  # appel porgramme de mise en place init
    Theta_abs = 90

    print("position init abs : X = %f, Y = %f, Theta = %f" % (X_abs, Y_abs, Theta_abs))

    # Recherche des Odrive
    odrv0 = odrive.find_any()

    # récuperation cote + tirette
    cote = Switch.cote()  # Jaune = True, Violet = False

    # creation du dico avec les valeurs des points
    creation = Creation(cote)  # bool de l'interrupteur tirrette TODO : Prise en compte du coté dans Registre
    creation.main()
    # fin

    # récupération des valeurs des points
    recuperation = Recuperation(creation.chemin.dictionnaire)
    Registre_points = recuperation.main()
    # fin

    # Boucle Bloquante Tirette
    Switch.tirette()

    for P in range(len(Registre_points)):  # TODO : implementer la boucle for pour le déroulement de l'itinéraire

        # Traitement
        treatment = Treatment(X_abs, Y_abs, Theta_abs)
        Traj_list = treatment.step(P)  # Traj_list = [ Distance, Theta ]
        print("Traj_list = %f" % Traj_list)
        # fin


        # déplacements
        move = Move(odrv0)

            # Rotation
        Senslist = [True, True, True, True, True]
        move.rotation(Traj_list[1], Senslist)
            # fin

                # Recuperation de position instant 1er composante
        pos00 = odrv0.axis0.encoder.pos_estimate
        pos10 = odrv0.axis1.encoder.pos_estimate
                # fin

            # Translation
        if Traj_list >= 0:
            Senslist = [True, True, True, False, False]

        elif Traj_list < 0:
            Senslist = [False, False, False, True, True]

        move.translation(Traj_list[0], Senslist)
            # fin


                # Recuperation de position instant 2eme composantes
        pos01 = odrv0.axis0.encoder.pos_estimate
        pos11 = odrv0.axis1.encoder.pos_estimate
                # fin

        # fin

        # instant position
        positionate = Positionate(pos00, pos01, pos10, pos11, Traj_list[2])
        [X_abs, Y_abs, Theta_abs] = positionate.step()
        print("position abs : X = %f, Y = %f, Theta = %f" % (X_abs, Y_abs, Theta_abs))
        # fin

        print("dodging begin")

        # evitement
        # dodging = Dodging() # TODO : Coder dodging
        # fin

        print("dodging end")

if __name__ == "__main__":
    main()
