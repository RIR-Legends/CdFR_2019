#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
from Robot import Robot

##### LISTE DES ACTIONS POSSIBLES
#"Arret"
#"Transport"
#"Palet_Floor_In"
#"Palet_Wall_In"
#"Palet_Floor_Out"
#"Palet_Wall_Out"
##### FIN LISTE DES ACTIONS POSSIBLES

def main(lancer_exp = True):
    robot = Robot(lancer_exp)

    robot.move_to("Point0")
    robot.move_to("Point1")        ##Exemple pour se déplacer à un point
    #robot.action("Palet_Floor_In")    ##Exemple pour effectuer une action avec l'Arduino
    robot.move_to("Point2")
    robot.move_to("Point3")
    robot.move_to("Point31")
    robot.move_to("Point32")
    robot.move_to("Point4")
    robot.action("Palet_Wall_In")


if __name__ == '__main__':
    if len(sys.argv) == 1:
        main(sys.argv[1]) # Pour ne pas lancer l'expérience : 'python3 main.py False'
    main(True)
