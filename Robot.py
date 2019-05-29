#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from Communication.communication import Communication as Communication
from Deplacements.point import Point as Point
import Points.filedb

from Deplacements.param import Param as OdriveParam
from Deplacements.move import Move as Movements
#from Deplacements.chemin import Chemin as Parcours
from Deplacements.Treatment import Treatment as Treatment


#from RPlidar.RIR_rplidar import RPLidar as RPLidar

class Robot():
    def __init__(self):
        # Initialisation de la communication avec l'Arduino
        self.com = Communication() ### ATTENTION PEUT ETRE BLOQUANT

        # Initialisation informations extérieur
        self.side = None
        self.tirettePulled = False
        self.timer = time.time()

        # Initialisation ODrive
        self.Oparam = OdriveParam()
        #self.Oparam.RAZ()
        self.Oparam.config()
        self.Oparam.calib_always()

        # Intilialisation Trajectoire
        self.move = Movements(self.Oparam.odrv0)
        self.dbPoints = filedb.fileDB(db="points")
        self.treatment = Treatment()
        self.thetaOrder = 0
        self.distanceOrder = 0
        self.currentPos = Point(0,0,0)

        # Initialisation Lidar et SLAM
        self.lidar = RPLidar() ### ATTENTION PEUT ETRE BLOQUANT

    def checkSide(self):
        ''' A refaire selon branchement sur Rasp '''
        #while self.com.OrangeSide == None:
        #    self.com.checkAndRead()
        #self.side = "Violet"
        #if OrangeSide:
        #    self.side = "Orange"
        #return self.side

    def checkTimer(self):
        Now = time.time() - DepartTime
        

    def waitingTrigger(self):
        ''' A refaire selon branchement sur Rasp '''
        #while self.com.Tirette:
        #    self.com.checkAndRead()
        self.timer = time.time()

    def stopAll(self):
        self.move.stop()
        self.com.send(Communication.MSG["Arret"])

    def getOrder(self,departPoint,arrivalPoint):
        res = self.treatment(departPoint,arrivalPoint)
        self.thetaOrder = res[1]
        self.distanceOrder = res[0]

    def getDataDB(self,name):
        ''' Va chercher et retourne le point associé au name dans la base de donnée '''
        data = literal_eval(self.dbPoints.get(name))
        return Point(data[0],data[1],data[2]) # Pour l'instant seuls les Points sont considérés dans la base de données
