#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import Robot



def main():
    # Initialisation
    robot = Robot()
    checkUp()
    
    # Attente du d�part (Tirette)
    robot.waitingTrigger()
    #### Lancer le timer ICI
    
    # Recupere consigne
    getOrder(robot.currentPos,robot.parcours.dictionnaire['Point1'])
    # Effectue le mouvement
    robot.move.translation(50)
    robot.move.rotation(90)
    # Doit effectuer une mise � jour de la position du robot (robot.currentPos). Pour l'instant on fait confiance � l'Odrive.
    
def checkUp():
    robot.checkSide()
    robot.setParcours()
    



if __name__ == '__main__':
    main()
