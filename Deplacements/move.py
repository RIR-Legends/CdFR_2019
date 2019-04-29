#!/usr/bin/env python3
from __future__ import print_function
#from Deplacements.Treatment import Treatment



import odrive
from odrive.enums import *  # a checker
import time
from math import *

class Move:
    def __init__(self): #, p1, p2
        #self.Treat = Treatment()
        #self.info_move = self.Treat.step(p1, p2)

        # Robot physical constant
        self.WheelDiameter = 80     # en mm
        self.nbCounts = 8192    # Nombre de tics pr un tour d'encoder
        self.AxlTrack = 275    # en mm mais la valeur est douteuse
        self.WheelPerimeter = self.WheelDiameter * pi  # en mm

        # coding features
        self.errorMax = 40      # unité ?
        self.odrv0 = odrive.find_any()

    def wait_end_move(self, axis, goal, errorMax):

        # fonction appelée à la fin des fonctions Move pour assurer
        # l'execution complète du mouvement/déplacement.

        avg = 10 * [0]
        index = 0
        movAvg = abs(goal - axis.encoder.pos_estimate)
        while movAvg >= errorMax:
            print("Encoder 0 : ", self.odrv0.axis0.encoder.pos_estimate,"   Encoder 1 : ", self.odrv0.axis1.encoder.pos_estimate)

            for i in range(index, 10):
                index = 0
                avg[i] = abs(goal - axis.encoder.pos_estimate)

            movAvg = 0
            for i in range(0, 10):
                movAvg += avg[i] / 10

    def translation(self, distance):
        # fonction qui permet d'avancer droit pour une distance donnée en mm
        print("Lancement d'une Translation de %f mm" % distance)
        # Distance / Perimètre = nb tour a parcourir
        target = abs(float(self.odrv0.axis0.encoder.pos_estimate) + (self.nbCounts * distance)/self.WheelPerimeter)
        nbTours = target/self.nbCounts
        print("Nombre de tours de roue effectué : %f" % nbTours)
        self.odrv0.axis0.controller.move_to_pos(-target)
        # Voir si utilisation necessaire des threads
        self.odrv0.axis1.controller.move_to_pos(target)
        time.sleep(1)
        # Attente de la fin du mouvement
        #self.wait_end_move(self.odrv0.axis0, target, self.errorMax)
        #self.wait_end_move(self.odrv0.axis1, target, self.errorMax)


    def rotation(self, angle):
        print("Lancement d'une Rotation de %f°" % angle)

        # calcul du périmètre de la roue
        self.WheelPerimeter = self.WheelDiameter * pi
        # calcul du nombre de ticks a parcourir pour tourner sur place de l'angle demandé
        RunAngle = (float(angle) * pi * self.AxlTrack ) / 360.0
        pos_estimate = float((self.odrv0.axis0.encoder.pos_estimate + self.odrv0.axis1.encoder.pos_estimate)/2.0)
        target = abs( pos_estimate + (self.nbCounts * RunAngle) / self.WheelPerimeter)
        nbTours = target/self.nbCounts

        # Action ! :
        print("Nombre de tours de roue effectué : %f" % nbTours)
        self.odrv0.axis0.controller.move_to_pos(target)
        self.odrv0.axis1.controller.move_to_pos(target)
        time.sleep(1)

        # Attente de la fin du mouvement
        #self.wait_end_move(self.odrv0.axis0, target, self.errorMax)
        #self.wait_end_move(self.odrv0.axis1, target, self.errorMax)

    def stop(self):
        # Met la vitessea des roues à 0.
        print("Le robot s'arrête")
        self.odrv0.axis0.controller.speed(0)
        self.odrv0.axis1.controller.speed(0)

    def initialisation(self):
        # Thibault
        pass
