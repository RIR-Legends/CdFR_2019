#!/usr/bin/env python3

from __future__ import print_function
import time
import param as p
import move as m

def demo_1() :

    move = m.Move()

    time.sleep(0.1)

    '''time.sleep(1)
    move.translation(50)
    time.sleep(1)
    move.rotation(-180)
    time.sleep(1)
    move.rotation(45)
    time.sleep(1)
    move.rotation(0) # position initiale définie à la mise sous tension des batteries'''
    #move.translation(50)
    #time.sleep(3)
    move.rotation(90)
    time.sleep(3)
    move.rotation(0)
    time.sleep(3)
    move.rotation(90)
    time.sleep(3)
    move.rotation(0)
    time.sleep(3)
    move.rotation(90)
    time.sleep(3)
    move.rotation(0)

param = p.Param()
param.config()
param.calib_always()

demo_1()

param.unlock_wheels()

print('Fin du programme')

#odrv0.reboot()
