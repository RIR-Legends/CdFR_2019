#!/usr/bin/env python3
from __future__ import print_function
#from Deplacements.Treatment import Treatment


import MCP3008
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
        self.errorMax = 10      # unité ?
        self.odrv0 = odrv0
        # variables de sauvegarde des positions réelles (TEST)
        #self.pos_setpoint0 = 0
        #self.pos_setpoint1 = 0


    def wait_end_move(self, axis, goal, errorMax):

        # fonction appelée à la fin des fonctions Move pour assurer
        # l'execution complète du mouvement/déplacement.

        avg = 10 * [0]
        index = 0
        movAvg = abs(goal - axis.encoder.pos_estimate)
        while movAvg >= errorMax:
            print("Encoder : ", axis.encoder.pos_estimate,"Goal/Target : ", goal, "movAvg : ", movAvg )
            for i in range(index, 10):
                index = 0
                avg[i] = abs(goal - axis.encoder.pos_estimate)

            movAvg = 0
            for i in range(0, 10):
                movAvg += avg[i] / 10

    def translation_rel(self, distance):

        # Fonction qui fait avancer droit le robot d'une distance donnée en mm
        print("Lancement d'une Translation de %f mm" % distance)

        # Controle de la Position en Relatif:
        # Distance / Perimètre = nb tour a parcourir
        target0 = - (self.nbCounts * distance)/self.WheelPerimeter
        target1 = (self.nbCounts * distance)/self.WheelPerimeter
        # Action !
            #move_inc en phase test / erreure d'attribut
        self.odrv0.axis0.controller.move_incremental(target0, )   #moteur 0 inversé par rapport moteur 1
        self.odrv0.axis1.controller.move_incremental(target1, )

        # Attente de la fin du mouvement
        self.wait_end_move(self.odrv0.axis0, target0, self.errorMax)
        self.wait_end_move(self.odrv0.axis1, target1, self.errorMax)

        # Save la position en tics dans les variables pos_estimate
        pos_setpoint0 = self.odrv0.axis0.controller.pos_estimate
        odrv0.axis0.controller.pos_setpoint = pos_setpoint0
        pos_setpoint1 = self.odrv0.axis1.controller.pos_estimate
        odrv0.axis1.controller.pos_setpoint = pos_setpoint1



    def translation(self, distance):
        # fonction qui permet d'avancer droit pour une distance donnée en mm
        print("Lancement d'une Translation de %f mm" % distance)

        # Controle de la Position en Absolu:
                            # pos_estimate --> pos_setpoint   # Distance / Perimètre = nb tour a parcourir
        target0 = self.odrv0.axis0.encoder.pos_estimate - (self.nbCounts * distance)/self.WheelPerimeter
        target1 = self.odrv0.axis1.encoder.pos_estimate + (self.nbCounts * distance)/self.WheelPerimeter

        # Action ! # TEST avec capteurs evitement obstacle
        while self.odrv0.axis0.encoder.pos_estimate != target0 and self.odrv0.axis1.encoder.pos_estimate != target1 :
            for i in range(0,4):
                values[i]= readadc(i)
                if values[i]> 800:
                    self.odrv0.axis0.controller.speed(0)
                    self.odrv0.axis1.controller.speed(0)
                else:
                    self.odrv0.axis0.controller.move_to_pos(target0)
                    self.odrv0.axis1.controller.move_to_pos(target1)
                    # Attente de la fin du mouvement
                    self.wait_end_move(self.odrv0.axis0, target0, self.errorMax)
                    self.wait_end_move(self.odrv0.axis1, target1, self.errorMax)


        # [A TESTER] Save la position en tics dans les variables pos_estimate
        #odrv0.axis0.controller.pos_setpoint = self.odrv0.axis0.controller.pos_estimate
        #pos_setpoint0 = odrv0.axis0.controller.pos_setpoint
        #odrv0.axis1.controller.pos_setpoint = self.odrv0.axis1.controller.pos_estimate
        #pos_setpoint1 = odrv0.axis1.controller.pos_setpoint




    def rotation(self, angle):
        # Fonction qui fait tourner le robot sur lui même d'un angle donné en degré
        print("Lancement d'une Rotation de %f°" % angle)
        # calcul du nombre de ticks a parcourir pour tourner sur place de l'angle demandé
        RunAngle = (float(angle) * pi * self.AxlTrack ) / 360.0

        # Controle de la Position Angulaire en Absolu :
        target0 = self.odrv0.axis0.encoder.pos_estimate + (self.nbCounts * RunAngle) / self.WheelPerimeter
        target1 = self.odrv0.axis1.encoder.pos_estimate + (self.nbCounts * RunAngle) / self.WheelPerimeter
        #Action ! :
        while self.odrv0.axis0.encoder.pos_estimate != target0 and self.odrv0.axis1.encoder.pos_estimate != target1 :
            for i in range(0,4):
                values[i]= readadc(i)
                if values[i] > 800:
                    self.odrv0.axis0.controller.speed(0)
                    self.odrv0.axis1.controller.speed(0)
                else:
                    self.odrv0.axis0.controller.move_to_pos(target0)
                    self.odrv0.axis1.controller.move_to_pos(target1)
                    # Attente de la fin du mouvement
                    self.wait_end_move(self.odrv0.axis0, target0, self.errorMax)
                    self.wait_end_move(self.odrv0.axis1, target1, self.errorMax)



        # Save la position en tics dans les variables pos_estimate
        #pos_setpoint0 = self.odrv0.axis0.controller.pos_estimate
        #pos_setpoint1 = self.odrv0.axis1.controller.pos_estimate

    def stop(self):
        # Met la vitessea des roues à 0.
        print("Le robot s'arrête")
        self.odrv0.axis0.controller.speed(0)
        self.odrv0.axis1.controller.speed(0)

    def initialisation(self):
        # Thibault
        pass
