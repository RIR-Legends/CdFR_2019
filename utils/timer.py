# -*- coding: utf-8 -*-
#!/usr/bin/env python3

import threading
import time

import sys
sys.path.append('../')
sys.path.append('../Deplacement/Movement/')
from Deplacement.SLAM.RIR_rplidar import RPLidar
from move import *
from param import *

class RIR_timer():
    #def __init__(self, Communication, Moteur, Lidar):
    def __init__(self, Moteur, Lidar):
        self.launcher = threading.Thread(target=self.__RIR_timer, args=(Moteur, Lidar))
        self.duration = 20

    def __RIR_timer(self, motor, lidar):
        DepartTime = time.time()
        time.sleep(self.duration - 5)
        Now = time.time() - DepartTime
        while Now < self.duration:
            time.sleep(.1)
            Now = time.time() - DepartTime
            
        #Stop all
        lidar.stop()
        lidar.disconnect()
        #com.send(Communication.MSG["Arret"])
        motor[1].stop()
        motor[0].odrv0.reboot()
        
        # Try to do an action
        lidar.start_motor()
        move.translation(5000, [False]*5)
    
    def start_timer(self):
        self.launcher.start()

def main():
    # Initialisation
    lidar = RPLidar('/dev/ttyUSB0')
    param = Param()
    move = Move(param.odrv0)
    
    lidar.start_motor()
    param.config()
    param.calib()
    
    # Creation du timer
    timer = RIR_timer((param,move),lidar)

    # Lancement du timer
    timer.start_timer()
        
    # Action pour les tests
    move.translation(50000, [False]*5)


    # Attend que les threads se terminent (Bloquant)
    #thread.join()

if __name__ == '__main__':
    main()

