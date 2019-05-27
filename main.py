#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import Robot
from Timer import NinetySec


def main():
    # Initialisation
    robot = Robot()
    checkUp()
    timer = NinetySec()
    
    # Calibration point de départ (Mat)
    
    # Départ
    timer.start()
    
    # Deplacement à un point + Action

    # A la fin
    timer.join()
    
    
    #move("PointZero")
    
    
    

    
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
