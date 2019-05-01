#!/usr/bin/env python3

from __future__ import print_function
import time
import param as p
import move as m

param = p.Param()

def demo_simple(odrv0) :

    move = m.Move(odrv0)

    time.sleep(1)
    move.translation(50)
    time.sleep(2)
    move.rotation(90)
    time.sleep(2)
    move.translation(50)

def demo_relatif(odrv0) :
    move = m.Move(odrv0)
    #Test la fonction de controle de position relative par rapport à la précedente
    time.sleep(1)
    move.translation_rel(50)
    time.sleep(2)
    move.rotation(90)
    time.sleep(2)
    move.translation_rel(50)


def demo_tour(odrv0) :
    move = m.Move(odrv0)
    # Fait faire 3 tours de carreaux (chez Martial)
    for i in range(0,12):
        move.translation(350)
        time.sleep(2)
        move.rotation(-90)
        time.sleep(2)


#param.RAZ() # Lance fonction remise à zero des moteurs
param.config()  #Lance la configuration du odrive (vitesse max / acc max / decc max / courrant max ...)
param.calib_always()
# Choix de lancement des demos :
#demo_simple(param.odrv0)
#demo_tour(param.odrv0)
demo_rel(param.odrv0)



print('Fin du programme')

#odrv0.reboot()
