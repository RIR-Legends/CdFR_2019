#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import Robot
from Timer import NinetySec


def main():
    # Initialisation
    robot = Robot()
    checkUp()
    timer = NinetySec()
    
    # Calibration point de d�part (Mat)
    
    # D�part
    timer.start()
    
    # Deplacement � un point + Action

    # A la fin
    timer.join()
    
    
    #move("PointZero")
    
    
    

    
def checkUp():
    # Verification du cot� 


    #robot.checkSide()
    #robot.setParcours() #Load
    
def move(name):
    # Recupere consigne
    robot.getOrder(robot.currentPos,robot.getDataDB(name))
    
    # Effectue le mouvement
    robot.move.rotation(robot.thetaOrder)
    robot.move.translation(robot.distanceOrder)
    
    # Doit effectuer une mise � jour de la position du robot (robot.currentPos). Pour l'instant on fait confiance � l'Odrive.
    robot.currentPos = robot.getDataDB(name)


if __name__ == '__main__':
    main()
