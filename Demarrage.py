import RPi.GPIO as GPIO
import main as d#le fichier python de demarrage
from time import sleep

GPIO.setmode(GPIO.BOARD)

GPIO.setup(36,GPIO.IN)

nbBon = 0

for i in range(20):
    if GPIO.input(36)==1:
        nbBon = nbBon + 1
        sleep(0.1)
if nbBon > 15:
    print("je demarre")
    d.main(False, False) #Nom de la fonction a lancer
