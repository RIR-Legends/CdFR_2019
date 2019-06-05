# -*- coding: utf-8 -*-
#!/usr/bin/env python3

import threading
import time
import RPi.GPIO as GPIO

import sys
sys.path.append('../')
from Deplacement.SLAM.RIR_rplidar import RPLidar
sys.path.append('../Deplacement/Movement/') #Necessaire pour MCP3008
from communication import Communication
#from move import *
#from param import *
import Switch

class RIR_timer():
    def __init__(self, Communication, Moteur, Lidar, launch_exp = True, duration = 85):
        self.duration = duration
        self.launch_exp = launch_exp
        self.launcher = threading.Thread(target=self.__RIR_timer, args=(Communication, Moteur, Lidar))
        self.experience = threading.Thread(target=RIR_timer.__RIR_exp, args=())

        
    def __RIR_exp():
        pin = 16
        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(pin, GPIO.LOW)
        time.sleep(10)
        GPIO.output(pin, GPIO.HIGH)
        time.sleep(2)
        GPIO.output(pin, GPIO.LOW)

    def __RIR_timer(self, com, motor, lidar):
        DepartTime = time.time()
        time.sleep(self.duration - 7)
        Now = time.time() - DepartTime
        while Now < self.duration:
            time.sleep(.1)
            Now = time.time() - DepartTime
            
        #Stop all
        motor[1].stop()
        lidar.stop()
        lidar.disconnect()
        com.send(Communication.MSG["Arret"])
        motor[0].odrv0.reboot()
        
        # Try to do an action
        #try:
        #    com.waitEndMove(Communication.MSG["Palet_Floor_In"])
        #except:
        #    print("No Com Available")
        #try:
        #    lidar.start_motor()
        #except:
        #    print("No LiDAR Available")
        #try:
        #    move.translation(5000, [False]*5)
        #except:
        #    print("No Motor Available")
    
    def start_timer(self):
        self.launcher.start()
        if self.launch_exp:
            self.experience.start()

def main():
    # Initialisation
    lidar = RPLidar('/dev/ttyUSB0')
    param = Param()
    move = Move(param.odrv0)
    com = Communication('/dev/ttyACM1')
    
    lidar.start_motor()
    param.config()
    param.calib()
    com.waitEndMove(Communication.MSG["Initialisation"])
    time.sleep(1)
    
    # Creation du timer
    timer = RIR_timer(com, (param,move),lidar)
    
    # Lancement du timer
    timer.start_timer()

    # Action pour les tests
    move.translation(50000, [False]*5)


    # Attend que les threads se terminent (Bloquant)
    #thread.join()

if __name__ == '__main__':
    main()
