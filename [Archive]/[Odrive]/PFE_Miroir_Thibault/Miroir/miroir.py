#!/usr/bin/env python3

from __future__ import print_function
import time
from param2 import *

def Demo_Clk_SNCF() :
    # avec vitesse odrv0.axis1.trap_traj.config.vel_limit = 1409.502
    tourneAbs(36000)
    
    
def Demo_1() :

    time.sleep(0.1)
    tourneRel(90)
    time.sleep(1)
    tourneRel(-180)
    time.sleep(1)
    tourneRel(450)
    time.sleep(1)
    
    tourneAbs(0) # position initiale définie à la mise sous tension des batteries

    time.sleep(3)

#Find a connected ODrive (this will block until you connect one)
#print("finding an odrive...")


#print('Odrive found ! ')
#print("Bus voltage is " + str(odrv0.vbus_voltage) + "V")

calib()


#Demo_1()
Demo_Clk_SNCF()

fin()
print('Fin du programme')

#odrv0.reboot()      

#Convertisseur 220v --> 24v : 