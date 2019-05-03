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
    
    
    
    
    robot.move.translation(50)
    robot.rotation(90)
    
def checkUp():
    robot.checkSide()
    



if __name__ == '__main__':
    main()
