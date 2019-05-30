#!/usr/bin/env python3
# -*- coding: utf-8 -*-

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

    robot.move_to("Point1")        ##Exemple pour se déplacer à un point
    robot.action("Palet_Floor_In")    ##Exemple pour effectuer une action avec l'Arduino
    robot.move_to("Point2")


if __name__ == '__main__':
    if len(sys.argv) == 1:
        main(sys.argv[1]) # Pour ne pas lancer l'expérience : 'python3 main.py False'
    main(True)
