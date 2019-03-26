#!/usr/bin/env python3

from __future__ import print_function

import odrive
from odrive.enums import *  # a checker
import time
from math import *

odrv0 = odrive.find_any()


class Move:
    def __init__(self):

        # Robot physical constant
        self.WheelDiam = 80     # en mm
        self.nbCounts = 8192    # Nombre de tics pr un tour d'encoder
        self.AxlTrack = 0.6     # en mm mais la valeur est douteuse
        self.Wheel_Perimeter = self.WheelDiam * pi  # en mm

        # coding features
        self.error_max = 5      # unité ?

    def Stop(self):
        odrv0.axis0.controller.speed(0)
        odrv0.axis1.controller.speed(0)

    def WaitEndMove(self,axis, goal, errorMax):

        avg = 10 * [0]
        index = 0
        movAvg = abs(goal - axis.encoder.pos_estimate)
        while movAvg >= errorMax:
            print(odrv0.axis1.encoder.pos_estimate)
            for i in range(index, 10):
                index = 0
                avg[i] = abs(goal - axis.encoder.pos_estimate)

            movAvg = 0
            for i in range(0, 10):
                movAvg += avg[i] / 10

#''' PRENDRE EN COMPTE LE COEF DE FROTTEMENT (env. 0.65) ??? '''
# fonction qui permet d'avancer droit pour une distance donnée en mm

    def RunToPos(self, distance):

        # Distance / Perimètre = nb tour a parcourir
        target = (self.nbCounts * distance)/self.Wheel_Perimeter

        print(target)
        odrv0.axis0.controller.move_to_pos(-target)
        odrv0.axis1.controller.move_to_pos(target)
        self.WaitEndMove(odrv0.axis1, target, self.error_max)


    def TurnAbs(self, Angle):

        # definition des constantes liées au robot
        errorMax = 5
        wheelDiam = 80  # en mm
        axlTrack = 0.6  # Voie, distance entre roues. Valeur arbitraire ? en mm
        nbrCounts = 8192
        # calcul du périmètre de la roue
        self.Wheel_Perimeter = self.WheelDiam * pi
        # calcul du nombre de ticks a parcourir pour tourner sur place de l'angle demandé
        runAngle = Angle * pi * self.AxlTrack
        target = (self.nbCounts * runAngle) / self.Wheel_Perimeter

        # Action ! :
        print(odrv0.axis0.encoder.pos_estimate)
        odrv0.axis0.controller.move_to_pos(target)
        print(odrv0.axis1.encoder.pos_estimate)
        odrv0.axis1.controller.move_to_pos(target)

        # Attente de la fin du mouvement
        self.WaitEndMove(odrv0.axis0, target, errorMax)
        self.WaitEndMove(odrv0.axis1, target, errorMax)

    def Calib(self):

        # Find a connected ODrive (this will block until you connect one)
        print("finding an odrive...")
        odrive.find_any()
        print('Odrive found ! ')

        # 40Amp max dans le moteur (gros couple et sécurité pour pas fumer le moteur)
        odrv0.axis0.motor.config.current_lim = 40
        odrv0.axis1.motor.config.current_lim = 40

        # vmax en tick/s les encodeurs font 8192 tick/tours
        # controller.*.vel_limite prend le pas sur trap_traj.*.vel_limt
        odrv0.axis0.controller.config.vel_limit = 750000
        odrv0.axis1.controller.config.vel_limit = 750000

        # trap_traj parametrage des valeurs limit du comportement dynamique
        odrv0.axis1.trap_traj.config.vel_limit = 100000
        odrv0.axis0.trap_traj.config.vel_limit = 100000

        odrv0.axis0.trap_traj.config.accel_limit = 30000
        odrv0.axis1.trap_traj.config.accel_limit = 30000

        odrv0.axis0.trap_traj.config.decel_limit = 30000
        odrv0.axis1.trap_traj.config.decel_limit = 30000

        '''  # [EN DEV] Fonction pour lancer la calibration si elle n'a pas déjà été lancée '''
        # if odrv0.axis1.motor.is_calibrated == False:
        if odrv0.axis1.current_state == 1:  # AXIS_STATE_IDLE

            print("etat courant" + str(odrv0.axis1.current_state))

            print("starting calibration...")

            odrv0.axis1.requested_state = 3  # AXIS_STATE_FULL_CALIBRATION_SEQUENCE

            while odrv0.axis1.current_state != 1:  # AXIS_STATE_IDLE
                time.sleep(1)

            odrv0.axis1.encoder.pos_estimate()

            odrv0.axis1.requested_state = 8  # AXIS_STATE_CLOSED_LOOP_CONTROL  , mise en mode boucle fermée

        else:
            odrv0.axis1.encoder.pos_estimate()
            print("after else")


def Fin():

    odrv0.axis1.requested_state = 1  # AXIS_STATE_IDLE , libère le moteur : boucle ouverte

def TurnRel(Angle):
    # definition des constantes liées au robot
    errorMax = 5
    weelDiam = 80
    axlTrack = 0.6  # Voie, distance entre roues
    nbrCounts = 8192
    # calcul du périmètre de la roue
    weelPerim = weelDiam * pi
    # calcul du nombre de ticks a parcourir pour tourner sur place de l'angle demandé
    runAngle = Angle * pi * axlTrack
    target = (nbrCounts * runAngle) / weelPerim
    targRel = target + (odrv0.axis0.encoder.pos_estimate + odrv0.axis0.encoder.pos_estimate)/2

    # Action ! :
    print(odrv0.axis0.encoder.pos_estimate)
    odrv0.axis0.controller.move_to_pos(targRel)
    print(odrv0.axis1.encoder.pos_estimate)
    odrv0.axis1.controller.move_to_pos(-targRel)

    # Attente de la fin du mouvement
    Move.WaitEndMove(odrv0.axis0, targRel, Move.error_max)
    Move.WaitEndMove(odrv0.axis1, targRel, Move.error_max)
