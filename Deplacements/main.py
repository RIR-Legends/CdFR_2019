#!/usr/bin/env python3

from __future__ import print_function
import time
import param as p

def Demo_1() :

    move = p.Move

    time.sleep(0.1)
    move.RunToPos(500)
    time.sleep(1)
    move.turnRel(-180)
    time.sleep(1)
    move.RunToPos(200)
    time.sleep(1)

    move.turnAbs(0)  # position initiale définie à la mise sous tension des batteries

    time.sleep(3)

    move.fin()


move = p.Move

move.Calib()
