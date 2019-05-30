#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
sys.path.append('utils/')
sys.path.append('Deplacement/')
sys.path.append('Deplacement/utils')
sys.path.append('Deplacement/Movement')
sys.path.append('Deplacement/SLAM')

from point import Point
import filedb
import Switch
from communication import Communication
from param import Param
from move import Move
from Trajectoire_bis import Trajectoire
from RIR_rplidar import RPLidar #from Lidar import Lidar
from utils.timer import RIR_timer


class Robot():
    def __init__(self, lancer_exp = True, MatCode = False):
        # Initialisation variables
        self.db = filedb.fileDB(db = "../Points")
        self.__lastpoint = Point.get_db_point("PointDepart", self.db)
        self.__side = Switch.cote()
        self.__com = Communication('/dev/ttyACM0')
        self.__Oparam = Param()
        self.__move = Move(self.Oparam.odrv0)
        self.__MatCode = MatCode
        self.__traj = Trajectoire(param = self.__Oparam, move = self.__move, point = self.__lastpoint, Solo = self.__MatCode)
        self.__lidar = RPLidar('/dev/ttyUSB0') #self.__lidar = Lidar('/dev/ttyUSB0')
        self.__timer = RIR_timer(self.com, (self.param,self.move), self.lidar, launch_exp) # Test: placé avant __init_physical
                
        self.__init_physical()
        self.set_ready()

    def __init_physical(self):
        self.__lidar.start_motor() # A retirer si lidar = Lidar
        self.__Oparam.config()
        self.__Oparam.calib()
        self.__com.waitEndMove(Communication.MSG["Initialisation"])

    def set_ready(self):
        Switch.tirette()
        self.__timer.start_timer()
        if self.__MatCode:
           self.__traj.solo_launcher() #Mat's code
    
    def move_to(self, point_name):
        self.__lastpoint = Point.get_db_point(point_name, self.db)
        if not self.__side:
            self.__lastpoint.mirror()
        
        self.__traj.process(self.__lastpoint)
        
    def action(self, action_name, dist_deploiement = 100):
        if action_name == "Transport" or action_name == "Palet_Floor_In" or action_name =="Palet_Floor_Out":
            self.com.waitEndMove(Communication.MSG[action_name])
        elif action_name == "Arret":
            self.com.send(Communication.MSG[action_name])
        elif action_name == "Palet_Wall_In" or action_name == "Palet_Wall_Out":
            self.com.send(Communication.MSG[action_name])
            
            while not self.com.Avancer:
                self.com.read()
            temp_point = self.__lastpoint
            if action_name == "Palet_Wall_In":
                temp_point.x += dist_deploiement
            else:
                temp_point.x -= dist_deploiement
            self.__traj.process(temp_point)
            
            self.com.send(Communication.MSG["Action_Finished"])
            while not self.com.Reculer:
                self.com.read()
            self.__traj.process(self.__lastpoint)
            
            self.com.send(Communication.MSG["Action_Finished"])
            while not self.com.readyNext:
                self.com.read()
