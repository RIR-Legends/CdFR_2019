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

def main(lancer_exp = True, MatCode = False, db = "Points"):
    robot = Robot(lancer_exp, MatCode, db = db, defaultPoint = "Point0", setTimer = True)

    #robot.move_to("Point0")
    robot.action("Palet_Floor_In")
    robot.move_to("Point1")        ##Exemple pour se déplacer à un point
    #robot.action("Palet_Floor_In")    ##Exemple pour effectuer une action avec l'Arduino
    robot.move_to("Point2")
    robot.move_to("Point3")
    robot.move_to("Point4")
    robot.action("Palet_Floor_Out")
    robot.move_to("Point5")
    #robot.action("Palet_Floor_In")
    robot.move_to("Point6")
    #robot.action("Palet_Floor_Out")
    #robot.move_to("Point4")


if __name__ == '__main__':
    if len(sys.argv) == 2:
        main(sys.argv[1]=='True', sys.argv[2] == 'True')
    # Pour ne pas lancer l'expérience : 'python3 main.py False ___'
    # Pour lancer l'homologation par Mat : 'python3 main.py ___ True
    main()
