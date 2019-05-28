#!/usr/bin/env python3
import RPi.GPIO as GPIO
from time import sleep
# Set up du board (reférence n° port)
GPIO.setmode(GPIO.BOARD)

# definition de la pin comme pin d'entrée
GPIO.setup(7, GPIO.IN)
GPIO.setup(11, GPIO.IN)

# Lecture de la Pin
# GPIO.input(7) # GPAIO 4
# GPIO.input(11) # GPAIO 17

# Attente de réponse => TODO: test
def tirette():
    while GPIO.input(7) == 0: # boucle de check tirette relevée
        print("attente tirette")
        sleep(1)

def cote():
    if(GPIO.input(11) == 1): # TODO: Validé
        print("Jaune")
        return True

    if(GPIO.input(11) == 0): # TODO: Validé
        print("Violet")
        return False

def main():
    tirette()
    cote()



if __name__ == '__main__':
    main()
