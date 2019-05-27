import RPi.GPIO as GPIO

# Set up du board (reférence n° port)
GPIO.setmode(GPIO.BOARD)

# definition de la pin comme pin d'entrée
GPIO.setup(7, GPIO.IN)
GPIO.setup(11, GPIO.IN)

# Lecture de la Pin
# GPIO.input(7) # GPAIO 4
# GPIO.input(11) # GPAIO 17

# Attente de réponse => TODO: test
GPIO.wait_for_edge(7, GPIO.FALLING) # ou GPIO.RISING

if(GPIO.input(11) == 1): # TODO: Test
    print("Jaune")
    return True

if(GPIO.input(11) == 0): # TODO: Test
    print("Violet")
    return False
