#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from Communication.communication import Communication as Communication
from Deplacements.point import Point as Point

from Deplacements.param import Param as OdriveParam
from Deplacements.move import Move as Movements
from Deplacements.Chemin import Chemin as Parcours
from Deplacements.Treatment import Treatment as Treatment

from RPlidar.RIR_rplidar import RPLidar as RPLidar

class Robot():
    def __init__(self):
        self.com = Communication()
        
        self.side = None
        
        
        self.Oparam = OdriveParam()
        #self.Oparam.RAZ()
        self.Oparam.config()
        self.Oparam.calib_always()
        
        self.move = Movements(self.Oparam.odrv0)
        self.parcours = Parcours()
        self.treatment = Treatment()
        self.thetaOrder = 0
        self.distanceOrder = 0
        self.currentPos = Point(0,0,0)
        
        
        self.lidar = RPLidar()
        
    def checkSide(self):
        while self.com.OrangeSide == None:
            self.com.checkAndRead()
        self.side = "Violet"
        if OrangeSide:
            self.side = "Orange"
        return self.side
        
    def waitingTrigger(self):
        while self.com.Tirette:
            self.com.checkAndRead()
            
    def stopAll(self):
        self.move.stop()
        self.com.send(Communication.MSG["Arret"])
    
    def setParcours(self):
        self.parcours.add_point('Départ', 0, 0, 0)
        self.parcours.add_point('Point1', 100, 0, 0)
        self.parcours.add_point('Point2', 100, 100, 0)
        self.parcours.add_point('Point3', 100, 100, 90)
        self.parcours.add_point('Point4', 200, 200, 90)
    
    def getOrder(self,departPoint,arrivalPoint):
        res = self.treatment(departPoint,arrivalPoint)
        self.thetaOrder = res[1]
        self.distanceOrder = res[0]
    
    

        
            
class Motor