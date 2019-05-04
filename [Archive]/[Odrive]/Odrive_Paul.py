#!/usr/bin/env python3
"""
Example usage of the ODrive python library to monitor and control ODrive devices
"""

from __future__ import print_function

import odrive
from odrive.enums import *
import time
import math




# fonction qui attent la fin du mouvement prend comme agument le point à atteindre et l'erreur

def waitEndMove(Axe,pointF,erreurMax) :
    moy = 10*[0]
    index = 0
    moyGliss = abs(pointF - Axe.encoder.pos_estimate)
    while moyGliss >= erreurMax :
        #print(moyGliss)
        for i in range(index,10) :
            index = 0
            moy[i] = abs(pointF - Axe.encoder.pos_estimate)
        
        moyGliss = 0
        for i in range(0,10):
            moyGliss += moy[i]/10
        
    
    
  
    
        
# fonction qui permet d'avancer droit pour une distance donnée en mm
def avanceToPos(Distance) :
    # definition des constante du robot
    erreurMax = 5
    DiamRoue = 80
    nbTicksTours = 8192
    AvanceUnTourRoue = DiamRoue * 3.14
    # calcul du nombre de tics a parcourir
    pointF = (nbTicksTours * Distance)/AvanceUnTourRoue
    #print(pointF)
    my_drive.axis0.controller.move_to_pos(-pointF)
    my_drive.axis1.controller.move_to_pos(pointF)
    waitEndMove(my_drive.axis1,pointF,erreurMax)
    
# Fonction qui fait tourner les moteurs en sens inverse pour effectuer une rotation du robot de l'angle demandé
def tourne(angleDeg) :
    # definition des constante liées au robot 
    erreurMax = 5
    EntreRoue = 0.6
    DiamRoue = 80
    nbTicksTours = 8192
    #calcul du périmetre de la roue 
    AvanceUnTourRoue = DiamRoue * 3.14
    # calcul du nombre de ticks a parcourir pour tourner sur place de l'angle demandé
    pointFmm = angleDeg*3.14*EntreRoue
    pointF = (nbTicksTours * pointFmm)/AvanceUnTourRoue
    #Action !
    #print(pointF)
    my_drive.axis0.controller.move_to_pos(pointF)
    my_drive.axis1.controller.move_to_pos(pointF)
    # Attente de la fin du mouvement
    waitEndMove(my_drive.axis0, pointF, erreurMax)

# Find a connected ODrive (this will block until you connect one)
print("finding an odrive...")
my_drive = odrive.find_any()

print('trouvé !!!')

# Find an ODrive that is connected on the serial port /dev/ttyUSB0
#my_drive = odrive.find_any("serial:/dev/ttyUSB0")
# 50Amp max dans le moteur (gros couple et sécurité pour pas fumer le moteur)
#my_drive.motor.config.current_lim = 50
# vmax en tick/s les encodeurs font 8192 tick/tours
my_drive.axis0.controller.config.vel_limit = 100000 
my_drive.axis1.controller.config.vel_limit = 100000

my_drive.axis0.trap_traj.config.vel_limit = 100000 
my_drive.axis1.trap_traj.config.vel_limit = 100000

my_drive.axis0.trap_traj.config.accel_limit = 30000 
my_drive.axis1.trap_traj.config.accel_limit = 30000

my_drive.axis0.trap_traj.config.decel_limit = 30000 
my_drive.axis1.trap_traj.config.decel_limit = 30000

#affichage de la fenetre de graph position
#from odrive.utils import start_liveplotter
#start_liveplotter(lambda: [my_drive.axis0.encoder.pos_estimate])

# Calibrate motors and wait for it to finish
print("starting calibration...")
my_drive.axis0.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
my_drive.axis1.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE


while my_drive.axis0.current_state != AXIS_STATE_IDLE and my_drive.axis1.current_state != AXIS_STATE_IDLE:
    time.sleep(0.1)



my_drive.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL # mise en mode boucle fermé
my_drive.axis1.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL # mise en mode boucle fermé

# To read a value, simply read the property
print("Bus voltage is " + str(my_drive.vbus_voltage) + "V")

# Or to change a value, just assign to the property
#my_drive.axis0.controller.pos_setpoint = 3.14
#print("Position setpoint is " + str(my_drive.axis0.controller.pos_setpoint))

# And this is how function calls are done:
for i in [1, 2, 3, 4]:
    print('voltage on GPIO{} is {} Volt'.format(i, my_drive.get_adc_voltage(i)))


#declaration des variables
time.sleep(1)
erreurMax = 50
pointArrivemm = 400
pointArrive2 = 15
#atteint premier point
avanceToPos(pointArrivemm)
  
#atteint 2eme point

avanceToPos(pointArrive2)

"""
my_drive.axis0.controller.move_to_pos(pointArrivemm)
my_drive.axis1.controller.move_to_pos(pointArrivemm)
"""
#waitEndMove(my_drive.axis0,pointArrive2,erreurMax)

    
tourne(90)
  
avanceToPos(pointArrivemm)


print('Fin du programme')
# Assign an incompatible value:
my_drive.motor0.pos_setpoint = "I like trains"  # fails with `ValueError: could not convert string to float`


