#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from Communication.communication import Communication as Communication

from Deplacements.param import Param as OdriveParam
from Deplacements.move import Move as Movements

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
    
    
    
    
    

        
            
class Motor