#!/usr/bin/env python3
from __future__ import print_function
#from Deplacements.Treatment import Treatment



import odrive
from odrive.enums import *  # a checker
import time
from math import *

class Move:
    def __init__(self, odrv0): #, p1, p2
        #self.Treat = Treatment()
        #self.info_move = self.Treat.step(p1, p2)

        # Robot physical constant
        self.WheelDiameter = 80     # en mm
        self.nbCounts = 8192    # Nombre de tics pr un tour d'encoder
        self.AxlTrack = 275    # en mm mais la valeur est douteuse
        self.WheelPerimeter = self.WheelDiameter * pi  # en mm

        # coding features
        self.errorMax = 5      # unité ?
        self.odrv0 = odrv0

    def wait_end_move(self, axis, goal, errorMax):

        # fonction appelée à la fin des fonctions Move pour assurer
        # l'execution complète du mouvement/déplacement.

        avg = 10 * [0]
        index = 0
        movAvg = abs(goal - axis.encoder.pos_estimate)
        while movAvg >= errorMax:
            print("Encoder : ", axis.encoder.pos_estimate)
            print("Goal/Target : ", goal)
            print("movAvg : ", movAvg)
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
        target0 = self.odrv0.axis0.encoder.pos_estimate + (self.nbCounts * distance)/self.WheelPerimeter
        target1 = self.odrv0.axis1.encoder.pos_estimate + (self.nbCounts * distance)/self.WheelPerimeter

        # Action !
        self.odrv0.axis0.controller.move_to_pos(-target0)   #moteur 0 inversé par rapport moteur 1
        self.odrv0.axis1.controller.move_to_pos(target1)
        time.sleep(1)

        # Attente de la fin du mouvement
        self.wait_end_move(self.odrv0.axis0, -target0, self.errorMax)
        self.wait_end_move(self.odrv0.axis1, target1, self.errorMax)


    def rotation(self, angle):
        print("Lancement d'une Rotation de %f°" % angle)

        # calcul du périmètre de la roue
        self.WheelPerimeter = self.WheelDiameter * pi
        # calcul du nombre de ticks a parcourir pour tourner sur place de l'angle demandé
        RunAngle = (float(angle) * pi * self.AxlTrack ) / 360.0

        target0 = self.odrv0.axis0.encoder.pos_estimate + (self.nbCounts * RunAngle) / self.WheelPerimeter
        target1 = self.odrv0.axis1.encoder.pos_estimate + (self.nbCounts * RunAngle) / self.WheelPerimeter

        #Action ! :
        self.odrv0.axis0.controller.move_to_pos(target0)
        self.odrv0.axis1.controller.move_to_pos(target1)
        time.sleep(1)

        # Attente de la fin du mouvement
        self.wait_end_move(self.odrv0.axis0, target0, self.errorMax)
        self.wait_end_move(self.odrv0.axis1, target1, self.errorMax)

    def stop(self):
        # Met la vitessea des roues à 0.
        print("Le robot s'arrête")
        self.odrv0.axis0.controller.speed(0)
        self.odrv0.axis1.controller.speed(0)

    def initialisation(self):
        # Thibault
        pass
