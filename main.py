#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#import Robot
import sys
from utils.timer import RIR_timer
import utils.Switch as Switch

sys.path.append('Deplacement/')
sys.path.append('Deplacement/Movement/') #Necessaire pour MCP3008
from SLAM.RIR_rplidar import RPLidar
import Trajectoire
from move import *
from param import *
from utils.communication import Communication

def main():
    # Initialisation
    com = Communication('/dev/ttyACM0')
    lidar = RPLidar('/dev/ttyUSB0')
    param = Param()
    move = Move(param.odrv0)
    
    lidar.start_motor()
    param.config()
    param.calib()
    com.waitEndMove(Communication.MSG["Initialisation"])
    time.sleep(1)
    
    # Creation du timer
    timer = RIR_timer(com, (param,move), lidar, launch_exp = True)
    
    # Lancement du timer
    Switch.tirette()
    timer.start_timer()
    
    # Lancement de trajectoire + Tirette
    Trajectoire.main(param, move, False)


if __name__ == '__main__':
    main()
