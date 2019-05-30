#!/usr/bin/env python3

# Import librairies externes
from __future__ import print_function
import odrive
import sys

# Import programme Robot
from Post_treatment import PostTreatment
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


class Trajectoire():
    def __init__(self, param, move, Solo = True):
        self.Solo = Solo
        self.param = param
        self.move = move

        if self.Solo:
            # initialisation des Odrives
            self.param = Param() # a récupéré en argument de la fonction
            self.param.config()
            self.param.calib()
            print("fin de de calibration")
        
        # initialisation des paramètres ABS
        self.X_abs = 500  # appel programme de mise en place init
        self.Y_abs = 0  # appel porgramme de mise en place init
        self.Theta_abs = 90
        print("position init abs : X = %f, Y = %f, Theta = %f" % (self.X_abs, self.Y_abs, self.Theta_abs))        

        # Récupération de la carte Odrive
        self.odrv0 = self.param.odrv0

        # creation du dico avec les valeurs des points
        creation = Creation()  # bool de l'interrupteur tirrette
        creation.main()
        # fin
    
        # récupération des valeurs des points
        recuperation = Recuperation(creation.chemin.dictionnaire)
        self.Registre_points = recuperation.main()
        print(self.Registre_points)
        # fin

        # initialisation des classes
        self.positionate = Positionate()

        if self.Solo:
            self.move = Move(self.odrv0)      # a récupéré en argument
            
            # Boucle Bloquante Tirette
            Switch.tirette()
            
            self.solo_launcher()

    def solo_launcher(self):
        for P in self.Registre_points:

            # Traitement
            treatment = Treatment(self.X_abs, self.Y_abs, self.Theta_abs)
            Traj_list = treatment.step(P)  # Traj_list = [ Distance, Theta ]
            print("Traj_list = %s" % Traj_list)
            # fin

            # ================================================= déplacements ===============================================

                # Rotation
            if Traj_list[1] != 0:   # Theta != 0
                Senslist = [True, True, True, True, True]
                self.move.rotation(Traj_list[1], Senslist)
                # fin

                    # Recuperation de position instant 1er composante
            pos00 = self.odrv0.axis0.encoder.pos_estimate
            pos10 = self.odrv0.axis1.encoder.pos_estimate
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

                print("liste des capteurs actifs demandé", Senslist)

                self.move.translation(Traj_list[0], Senslist)
                # fin

                # retour capteur collision
                # Recuperation de position instant 2eme composantes
            pos01 = self.odrv0.axis0.encoder.pos_estimate
            pos11 = self.odrv0.axis1.encoder.pos_estimate
            print("pos 01 = ", pos01)
            print("pos 11 = ", pos11)
                # fin

            # instant position
            [self.X_abs, self.Y_abs, self.Theta_abs] = self.positionate.step(pos00, pos01, pos10, pos11, Traj_list[1])
            print("position Après translation abs : X = %f, Y = %f, Theta = %f" % (self.X_abs, self.Y_abs, self.Theta_abs))
            # fin

            # Recalculation pour l'iclinaison finale du robot
            FinalAngle = PostTreatment(self.Theta_abs).step(P)
                # fin

            # Rotation
            if FinalAngle != 0:  # Theta != 0
                Senslist = [True, True, True, True, True]
                self.move.rotation(FinalAngle, Senslist)
                # fin

            # instant position
            self.Theta_abs = self.positionate.step_theta(FinalAngle)
            print("position Après repositionnement Ang. abs : X = %f, Y = %f, Theta = %f" % (self.X_abs, self.Y_abs, self.Theta_abs))
            # fin

            # ============================================= fin ============================================================

            print("dodging begin")

            # evitement
            # dodging = Dodging() # TODO : Coder dodging
            # fin

            print("dodging end")

if __name__ == "__main__":
    robot = Trajectoire(None, None)
