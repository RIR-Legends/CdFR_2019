#!/usr/bin/env python3

from __future__ import print_function
import time
import param as p

def demo_1() :

    move = p.Move

    time.sleep(0.1)
    move.turn_abs(90)
    time.sleep(1)
    move.run_to_pos(50)
    move.turn_abs(-180)
    time.sleep(1)
    move.turn_abs(450)
    time.sleep(1)
    move.turn_abs(0) # position initiale définie à la mise sous tension des batteries
    time.sleep(3)
    move.run_to_pos(50)


move = p.Move()

move.calib()

demo_1()

fin()

print('Fin du programme')

#odrv0.reboot()
