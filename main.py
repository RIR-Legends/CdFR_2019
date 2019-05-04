#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import Robot



def main():
    # Initialisation
    robot = Robot()
    checkUp()
    
    # Attente du départ (Tirette)
    robot.waitingTrigger()
    #### Lancer le timer ICI
    #### Lancer le thread de détection
    
    move("PointZero")
    
    
    

    
def checkUp():
    robot.checkSide()
    #robot.setParcours() #Load
    
def move(name):
    # Recupere consigne
    robot.getOrder(robot.currentPos,robot.getData(name))
    
    # Effectue le mouvement
    robot.move.rotation(robot.thetaOrder)
    robot.move.translation(robot.distanceOrder)
    
    # Doit effectuer une mise à jour de la position du robot (robot.currentPos). Pour l'instant on fait confiance à l'Odrive.
    robot.currentPos = robot.getData(name)


if __name__ == '__main__':
    main()
