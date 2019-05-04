#!/usr/bin/env python3

from __future__ import print_function

import odrive
from odrive.enums import *
import time
import math

odrive = odrive.find_any()


def waitEndMove(Axe,pointF,erreurMax) :

    odrv0 = odrive

    moy = 10*[0]
    index = 0
    moyGliss = abs(pointF - Axe.encoder.pos_estimate)
    while moyGliss >= erreurMax :
        print(odrv0.axis1.encoder.pos_estimate)
        for i in range(index,10) :
            index = 0
            moy[i] = abs(pointF - Axe.encoder.pos_estimate)

        moyGliss = 0
        for i in range(0,10):
            moyGliss += moy[i]/10

def tourneAbs(angleDeg) :

    odrv0 = odrive

    # definition des constante liées au robot
    erreurMax = 10
    ratio = 10.13375
    #ratio = 10.3235
    #ratio = 10.228625

    nbTicksTours = 8192
    #calcul du périmètre de la roue

    # calcul du nombre de ticks a parcourir pour tourner sur place de l'angle demandé
    AngleMoteur = angleDeg * ratio
    Goal = (nbTicksTours * AngleMoteur)/360

    print(odrv0.axis1.encoder.pos_estimate)
    odrv0.axis1.controller.move_to_pos(Goal)
    # Attente de la fin du mouvement
    waitEndMove(odrv0.axis1,Goal,erreurMax)


def tourneRel(angleDeg) :

    odrv0 = odrive

    # definition des constante liées au robot
    erreurMax = 50
    #ratio = 10.3235
    ratio = 10.13375
    #ratio = 10.2
    nbTicksTours = 8192

    # calcul du nombre de ticks a parcourir pour tourner sur place de l'angle demandé
    AngleMoteur = angleDeg * ratio
    Goal = (nbTicksTours * AngleMoteur)/360
    GoalRel = Goal + odrv0.axis1.encoder.pos_estimate
    #Action !
    print(odrv0.axis1.encoder.pos_estimate)
    odrv0.axis1.controller.move_to_pos(GoalRel)
    # Attente de la fin du mouvement
    waitEndMove(odrv0.axis1,GoalRel,erreurMax)


def calib() :

    # toutes les infos sur le paramétrage du Odrive se trouvent sur :
    # https://docs.odriverobotics.com/

    print("finding an odrive...")
    odrv0 = odrive
    print('Odrive found ! ')
    #Find a connected ODrive (this will block until you connect one)
    odrv0.axis1.motor.config.current_lim = 40

    #vmax en tick/s les encodeurs font 8192 tick/tours

    odrv0.axis1.controller.config.vel_limit = 750000

    #odrv0.axis1.trap_traj.config.vel_limit = 500000
    odrv0.axis1.trap_traj.config.vel_limit = 1409.502

    odrv0.axis1.trap_traj.config.accel_limit = 30000

    odrv0.axis1.trap_traj.config.decel_limit = 30000

    #if odrv0.axis1.motor.is_calibrated == False:
    if odrv0.axis1.current_state == 1:

        print("etat courant" + str(odrv0.axis1.current_state))

        print("starting calibration...")

        odrv0.axis1.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE

        while odrv0.axis1.current_state != AXIS_STATE_IDLE:
            time.sleep(1)

        odrv0.axis1.encoder.pos_estimate

        odrv0.axis1.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL # mise en mode boucle fermée

    else:
        odrv0.axis1.encoder.pos_estimate
        print("after else")

def fin() :
    odrv0 = odrive
    odrv0.axis1.requested_state = AXIS_STATE_IDLE # mise en mode boucle fermée
