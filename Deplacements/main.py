#!/usr/bin/env python3

from __future__ import print_function
import time
import param as p
import move as m
from communication import Communication
param = p.Param()
com = Communication()


def demo_simple(odrv0) :

    move = m.Move(odrv0)

    time.sleep(1)
    move.translation(10000)
    #time.sleep(2)
    #move.rotation(90)
    #time.sleep(2)
    #move.translation(150)

def demo_relatif(odrv0) :
    move = m.Move(odrv0)
    #Test la fonction de controle de position relative (par rapport à pos précedente)
    time.sleep(1)
    move.translation(200)
    time.sleep(2)
    move.rotation(90)
    time.sleep(2)
    move.translation_rel(200)
    time.sleep(2)

def demo_tour(odrv0) :
    move = m.Move(odrv0)
    # Fait  3 tours de carreaux (chez Martial)
    for i in range(0,12):
        move.translation(350)
        time.sleep(2)
        move.rotation(-90)
        time.sleep(2)

def run_test(odrv0) :
    # Strategie proposé de parcour
    move = m.Move(odrv0)
    move.translation(400) # A verifier distante sortie Redium case to Red atom
    #com.send(Communication.MSG["Palet_Floor_In"]) #fct :Pickup Red atom
    move.translation(-150) # recule pour rentrer dans la REd case
    #com.send(Communication.MSG["Palet_Floor_Out"])# fct : Dropdown atom on the Red case
    move.translation(-150) # recule pour eviter le Red atom
    print("TRANS EN COURS")
    #move.stop()
    #print("STOP EN COURS")
    move.rotation(90)   #Tourne d'1/4 de tr vers la Green Case
    print("ROT EN COURS")

#param.RAZ() # Lance fonction remise à zero des moteurs
param.config()  #Lance la configuration du odrive (vitesse max / acc max / decc max / courrant max ...)
param.calib_always()

# Choix de lancement des demos :
demo_simple(param.odrv0)
#demo_tour(param.odrv0)
#demo_relatif(param.odrv0)
#run_test(param.odrv0)



print('Fin du programme')

#odrv0.reboot()
