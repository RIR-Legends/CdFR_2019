#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import Robot
from utils.timer import RIR_timer
import utils.Switch as Switch

sys.path.append('Deplacement/')
sys.path.append('Deplacement/Movement/') #Necessaire pour MCP3008
from SLAM.RIR_rplidar import RPLidar
import Trajectoire
from move import *
from param import *
from communication import Communication

def main():
    # Initialisation
    com = Communication('/dev/ttyACM1')
    lidar = RPLidar('/dev/ttyUSB0')
    param = Param()
    move = Move(param.odrv0)
    
    lidar.start_motor()
    param.config()
    param.calib()
    com.waitEndMove(Communication.MSG["Initialisation"])
    time.sleep(1)
    
    # Creation du timer
    timer = RIR_timer(com, (param,move), lidar)
    
    # Lancement du timer
    Switch.tirette()
    timer.start_timer()
    
    # Lancement de trajectoire + Tirette
    Trajectoire.main(param, move, False)
    
    
    
    

    
def checkUp():
    # Verification du coté 


    #robot.checkSide()
    #robot.setParcours() #Load
    
def move(name):
    # Recupere consigne
    robot.getOrder(robot.currentPos,robot.getDataDB(name))
    
    # Effectue le mouvement
    robot.move.rotation(robot.thetaOrder)
    robot.move.translation(robot.distanceOrder)
    
    # Doit effectuer une mise à jour de la position du robot (robot.currentPos). Pour l'instant on fait confiance à l'Odrive.
    robot.currentPos = robot.getDataDB(name)


if __name__ == '__main__':
    main()
