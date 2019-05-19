#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import Robot
from Timer import NinetySec


def main():
    # Initialisation
    robot = Robot()
    checkUp()
    timer = NinetySec()
    
    # D�part
    timer.start()

    # A la fin
    timer.join()
    
    
    #move("PointZero")
    
    
    

    
def checkUp():
    robot.checkSide()
    #robot.setParcours() #Load
    
def move(name):
    # Recupere consigne
    robot.getOrder(robot.currentPos,robot.getData(name))
    
    # Effectue le mouvement
    robot.move.rotation(robot.thetaOrder)
    robot.move.translation(robot.distanceOrder)
    
    # Doit effectuer une mise � jour de la position du robot (robot.currentPos). Pour l'instant on fait confiance � l'Odrive.
    robot.currentPos = robot.getData(name)


if __name__ == '__main__':
    main()
