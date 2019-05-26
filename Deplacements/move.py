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
        self.AxlTrack = 275    # en mm
        self.WheelPerimeter = self.WheelDiameter * pi  # en mm

        # coding features
        self.errorMax = 10      # unité ?
        self.OBS = False        # Init  Ostacle Detecté
        self.ActDone = False    #Init Action Faite
        self.odrv0 = odrv0      # Assignation du odrive name

    def wait_end_move(self, axis, goal, errorMax):

        # fonction appelée à la fin des fonctions Move pour assurer
        # l'execution complète du mouvement/déplacement.

        ''' [EN TEST ] CONDITION DE DETECTION D'OBSTACLE '''

        avg = 10 * [0]
        index = 0
        movAvg = abs(goal - axis.encoder.pos_estimate)
        self.ActDone = False

        # [A tester] (pour lecture capteur en fonction du sens de Translation)
        if goal > axis.encoder.pos_estimate:
            Sen = [1,2,3]
        else:
            Sen = [4,5]

        while movAvg >= errorMax:
            #print("Values vaut : ", MCP3008.readadc(1) )
            #print("Encoder : ", axis.encoder.pos_estimate,"Goal/Target : ", goal, "movAvg : ", movAvg )
            for i in Sen:
                if MCP3008.readadc(i) > 800 :
                    self.OBS = True
                    print("Obstacle détécté")
                    #self.detect_obs(axis, goal)
                    print("Values vaut : ", MCP3008.readadc(i) )
                    return 1

                else :
                    self.OBS = False
                    #self.detect_obs(axis, goal) #A revoir pour relancer le robot apres un arret.
                    for i in range(index, 10):
                        index = 0
                        avg[i] = abs(goal - axis.encoder.pos_estimate)
                    movAvg = 0
                    for i in range(0, 10):
                        movAvg += avg[i] / 10
        self.ActDone = True

    def detect_obs(self,axis, goal):
        # EN test pas utilisé ici
        if self.OBS == True :
            print("Obstacle détécté !")
            self.stop()
        else:
            print("Run !")
            axis.controller.move_to_pos(goal)


    def rotation(self, angle):
        # Fonction qui fait tourner le robot sur lui même d'un angle donné en degré
        print("Lancement d'une Rotation de %f°" % int(angle))
        # calcul du nombre de ticks a parcourir pour tourner sur place de l'angle demandé
        RunAngle = (float(angle) * pi * self.AxlTrack ) / 360.0

        # Controle de la Position Angulaire en Absolu :
        target0 = self.odrv0.axis0.encoder.pos_estimate + (self.nbCounts * RunAngle) / self.WheelPerimeter
        target1 = self.odrv0.axis1.encoder.pos_estimate + (self.nbCounts * RunAngle) / self.WheelPerimeter

        # Assignation de values avec valeur du capteur IR
        #values = MCP3008.readadc(1)

        # Action :
        """ [A inclure fonction évitement (OBS = True)] """
        """--------------------------------------------"""

        while 1: # [A tester] (a la place de condition en dessous)
            #self.odrv0.axis0.encoder.pos_estimate != target0 :#or self.odrv0.axis1.encoder.pos_estimate != target1:
            if self.OBS == False and self.ActDone == False:
                self.odrv0.axis0.controller.move_to_pos(target0)
                self.odrv0.axis1.controller.move_to_pos(target1)
                # Attente fin de mouvement SI aucun obstacle détécté
                self.wait_end_move(self.odrv0.axis0, target0, self.errorMax)
                #self.wait_end_move(self.odrv0.axis1, target1, self.errorMax)   #test sur 1 encoder pr l'instant
            #elif compteur_evitement == 3:
                #evitement(fdgf,sfv,sfg)
                #compteur_evitement = 0
            elif self.OBS == True and self.ActDone == False:
                # compteur_evitement =+ 1
                self.stop()
                time.sleep(2)
                self.OBS = False
            else :
                print("Rotation Terminée !")
                self.ActDone = False
                break




    def translation(self, distance):
        # fonction qui permet d'avancer droit pour une distance donnée en mm
        print("Lancement d'une Translation de %f mm" % int(distance))

        # Controle de la Position Longit en Absolu:
                                                        # Distance / Perimètre = nb tour a parcourir
        target0 = self.odrv0.axis0.encoder.pos_estimate - (self.nbCounts * distance)/self.WheelPerimeter
        target1 = self.odrv0.axis1.encoder.pos_estimate + (self.nbCounts * distance)/self.WheelPerimeter

        #Action ! :
        """ [A inclure fonction évitement (OBS = True)] """
        """--------------------------------------------"""
        while 1: # [A tester] (a la place de condition en dessous)
            #self.odrv0.axis0.encoder.pos_estimate != target0 :#or self.odrv0.axis1.encoder.pos_estimate != target1:
            if self.OBS == False and self.ActDone == False:
                self.odrv0.axis0.controller.move_to_pos(target0)
                self.odrv0.axis1.controller.move_to_pos(target1)
                # Attente fin de mouvement SI aucun obstacle détécté
                self.wait_end_move(self.odrv0.axis0, target0, self.errorMax)
                #self.wait_end_move(self.odrv0.axis1, target1, self.errorMax)   #test sur 1 encoder pr l'instant
            elif self.OBS == True and self.ActDone == False:
                self.stop()
                time.sleep(2)
                self.OBS = False
            else :
                print("Translation Terminée !")
                self.ActDone = False
                break



    def stop(self):
        # Met la vitessea des roues à 0.
        print("Le robot s'arrête")
        #self.odrv0.axis0.controller.speed(0)
        #self.odrv0.axis1.controller.speed(0)
        """ ou  POUR ARReTER LES MOTEURS : """

        self.odrv0.axis0.controller.set_vel_setpoint(0,0)
        self.odrv0.axis1.controller.set_vel_setpoint(0,0)
        self.odrv0.axis0.controller.pos_setpoint = self.odrv0.axis0.encoder.pos_estimate
        self.odrv0.axis1.controller.pos_setpoint = self.odrv0.axis1.encoder.pos_estimate
