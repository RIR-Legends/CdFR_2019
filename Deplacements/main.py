#!/usr/bin/env python3

from __future__ import print_function
import time
from param import *


def Demo_1() :

    time.sleep(0.1)
    turnRel(90)
    time.sleep(1)
    turnRel(-180)
    time.sleep(1)
    turnRel(450)
    time.sleep(1)
    
    turnAbs(0) # position initiale définie à la mise sous tension des batteries

    time.sleep(3)


calib()

Demo_1()

fin()

print('Fin du programme')

#odrv0.reboot()      

#Convertisseur 220v --> 24v : 
