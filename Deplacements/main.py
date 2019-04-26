#!/usr/bin/env python3

from __future__ import print_function
import time
import param as p

def demo_1() :

    move = p.Move()

    time.sleep(0.1)

    '''time.sleep(1)
    move.run_to_pos(50)
    time.sleep(1)
    move.turn_abs(-180)
    time.sleep(1)
    move.turn_abs(45)
    time.sleep(1)
    move.turn_abs(0) # position initiale définie à la mise sous tension des batteries'''
    move.run_to_pos(50)
    time.sleep(3)
    move.turn_abs(90)
    time.sleep(3)


move = p.Move()

move.calib()

demo_1()

move.fin()

print('Fin du programme')

#odrv0.reboot()
