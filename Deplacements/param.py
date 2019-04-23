#!/usr/bin/env python3

from __future__ import print_function



import odrive
from odrive.enums import *  # a checker
import time
from math import *
from point import Point


#odrv0 = odrive.find_any()


class Move:
    def __init__(self):

        # Robot physical constant
        self.WheelDiameter = 80     # en mm
        self.nbCounts = 8192    # Nombre de tics pr un tour d'encoder
        self.AxlTrack = 275    # en mm mais la valeur est douteuse
        self.WheelPerimeter = self.WheelDiameter * pi  # en mm

        # coding features
        self.errorMax = 10      # unité ?
        self.odrv0 = odrive.find_any()

    def stop(self):
        self.odrv0.axis0.controller.speed(0)
        self.odrv0.axis1.controller.speed(0)

    def wait_end_move(self, axis, goal, errorMax):

        avg = 10 * [0]
        index = 0
        movAvg = abs(goal - axis.encoder.pos_estimate)
        while movAvg >= errorMax:   # A commenter !!
            print(self.odrv0.axis1.encoder.pos_estimate)
            for i in range(index, 10):
                index = 0
                avg[i] = abs(goal - axis.encoder.pos_estimate)

            movAvg = 0
            for i in range(0, 10):
                movAvg += avg[i] / 10

#''' PRENDRE EN COMPTE LE COEF DE FROTTEMENT (env. 0.65) ??? '''
# fonction qui permet d'avancer droit pour une distance donnée en mm

    def run_to_pos(self, distance):
        print("Lancement de run_to_pos")
        # Distance / Perimètre = nb tour a parcourir
        target = (self.nbCounts * distance)/self.WheelPerimeter

        print(target)
        self.odrv0.axis0.controller.move_to_pos(-target)
        # Voir si utilisation necessaire des threads
        self.odrv0.axis1.controller.move_to_pos(target)
        self.wait_end_move(self.odrv0.axis1, target, self.errorMax)

    def turn_abs(self, Angle):

        print("Lancement de turn_abs")

        # calcul du périmètre de la roue
        self.WheelPerimeter = self.WheelDiameter * pi
        # calcul du nombre de ticks a parcourir pour tourner sur place de l'angle demandé
        runAngle = (float(Angle) * pi * self.AxlTrack ) / 360.0
        target = (self.nbCounts * runAngle) / self.WheelPerimeter

        # Action ! :
        print(self.odrv0.axis0.encoder.pos_estimate)
        self.odrv0.axis0.controller.move_to_pos(target)
        print(self.odrv0.axis1.encoder.pos_estimate)
        self.odrv0.axis1.controller.move_to_pos(target)

        # Attente de la fin du mouvement
        self.wait_end_move(self.odrv0.axis0, target, self.errorMax)
        self.wait_end_move(self.odrv0.axis1, target, self.errorMax)

    def calib(self):

        # Find a connected ODrive (this will block until you connect one)
        print("finding an odrive...")
        self.odrv0
        print('Odrive found ! ')

        # 40Amp max dans le moteur (gros couple et sécurité pour pas fumer le moteur)
        self.odrv0.axis0.motor.config.current_lim = 40
        self.odrv0.axis1.motor.config.current_lim = 40

        # vmax en tick/s les encodeurs font 8192 tick/tours
        # controller.*.vel_limite prend le pas sur trap_traj.*.vel_limt
        self.odrv0.axis0.controller.config.vel_limit = 750000
        self.odrv0.axis1.controller.config.vel_limit = 750000

        # trap_traj parametrage des valeurs limit du comportement dynamique
        self.odrv0.axis1.trap_traj.config.vel_limit = 100000
        self.odrv0.axis0.trap_traj.config.vel_limit = 100000

        self.odrv0.axis0.trap_traj.config.accel_limit = 30000
        self.odrv0.axis1.trap_traj.config.accel_limit = 30000

        self.odrv0.axis0.trap_traj.config.decel_limit = 30000
        self.odrv0.axis1.trap_traj.config.decel_limit = 30000

        print("starting calibration...")
        self.odrv0.axis0.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
        self.odrv0.axis1.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE

        while self.odrv0.axis0.current_state != 1 and self.odrv0.axis1.current_state != 1:
            time.sleep(0.1)

        self.odrv0.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL
        self.odrv0.axis1.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL


        '''  # [EN DEV] Fonction pour lancer la calibration si elle n'a pas déjà été lancée
        if self.odrv0.axis1.motor.is_calibrated == False:
        self.odrv0.axis0.requested_state = AXIS_STATE_MOTOR_CALIBRATION


        if self.odrv0.axis1.current_state == 1:  # AXIS_STATE_IDLE

            print("etat courant" + str(self.odrv0.axis1.current_state))

            print("starting calibration...")

            self.odrv0.axis1.requested_state = 3  # AXIS_STATE_FULL_CALIBRATION_SEQUENCE



            self.odrv0.axis1.encoder.pos_estimate()

            self.odrv0.axis1.requested_state = 8  # AXIS_STATE_CLOSED_LOOP_CONTROL  , mise en mode boucle fermée

        else:
            self.odrv0.axis1.encoder.pos_estimate()
            print("after else")
        '''

    def fin(self):

        self.odrv0.axis0.requested_state = 1
        # AXIS_STATE_IDLE , libère le moteur : boucle ouverte
        self.odrv0.axis1.requested_state = 1

def turn_rel(Angle):
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
    targRel = target + (self.odrv0.axis0.encoder.pos_estimate + self.odrv0.axis1.encoder.pos_estimate)/2

    # Action ! :
    print(self.odrv0.axis0.encoder.pos_estimate)
    self.odrv0.axis0.controller.move_to_pos(targRel)
    print(self.odrv0.axis1.encoder.pos_estimate)
    self.odrv0.axis1.controller.move_to_pos(-targRel)

    # Attente de la fin du mouvement
    Move.wait_end_move(self.odrv0.axis0, targRel, Move.error_max)
    Move.wait_end_move(self.odrv0.axis1, targRel, Move.error_max)
