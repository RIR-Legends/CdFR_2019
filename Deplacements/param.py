#!/usr/bin/env python3

from __future__ import print_function

import odrive
from odrive.enums import *  # a checker
import time
from math import *

class Param:
    def __init__(self):

        self.odrv0 = odrive.find_any()

    def config(self):
        self.odrv0
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

        self.odrv0.axis0.trap_traj.config.accel_limit = 10000
        self.odrv0.axis1.trap_traj.config.accel_limit = 10000

        self.odrv0.axis0.trap_traj.config.decel_limit = 30000
        self.odrv0.axis1.trap_traj.config.decel_limit = 30000

    def calib(self):

        # Find a connected ODrive (this will block until you connect one)
        print("finding an odrive...")
        self.odrv0
        print('Odrive found ! ')

        # Lance la calibration moteur si pas déjà faite
        if self.odrv0.axis0.motor.pre_calibrated == False and self.odrv0.axis1.motor.pre_calibrated == False:
            print("starting calibration...")
            self.odrv0.axis0.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
            self.odrv0.axis1.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE

            while self.odrv0.axis0.current_state != 1 and self.odrv0.axis1.current_state != 1:
                time.sleep(0.1)

            # Met les moteurs en boucle fermée
            self.odrv0.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL
            self.odrv0.axis1.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL

    def calib_always(self):

        # Find a connected ODrive (this will block until you connect one)
        print("finding an odrive...")
        self.odrv0
        print('Odrive found ! ')

        # Lance la calibration moteur si pas déjà faite
        print("starting calibration...")
        self.odrv0.axis0.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
        self.odrv0.axis1.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE

        while self.odrv0.axis0.current_state != 1 and self.odrv0.axis1.current_state != 1:
            time.sleep(0.1)

        # Met les moteurs en boucle fermée
        self.odrv0.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL
        self.odrv0.axis1.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL

    def unlock_wheels(self):

        self.odrv0.axis0.requested_state = 1
        # AXIS_STATE_IDLE , libère le moteur : boucle ouverte
        self.odrv0.axis1.requested_state = 1
