# -*- coding: utf-8 -*-
#!/usr/bin/env python3

import threading
import time

class RIR_timer():
    #def __init__(self, Communication, Moteur, Lidar):
    def __init__(self, Moteur, Lidar):
        self.launcher = threading.Thread(target=self.__RIR_timer, args=(Moteur, Lidar))

    def __RIR_timer(self, motor, lidar):
        DepartTime = time.time()
        time.sleep(5)
        Now = time.time() - DepartTime
        while Now < 10:
            time.sleep(.1)
            Now = time.time() - DepartTime
            
        #STOP ALL HERE
        lidar.stop()
        lidar.disconnect()
        #com.send(Communication.MSG["Arret"])
        motor[1].stop()
        motor[0].odrv0.reboot()
        
        # Try to do an action
        lidar.start_motor()
        move.translation(500)
    
    def start_timer(self):
        self.launcher.start()

def main():
    import sys
    sys.path.append('../')
    from Deplacement.SLAM.RIR_rplidar import RPLidar
    from Deplacement.Movement.move import *
    #from Deplacement.Movement.move import Move
    from Deplacement.Movement.param import *
    #from Deplacement.Movement.param import Param

    # Initialisation
    lidar = RPLidar('/dev/ttyUSB0')
    param = Param()
    move = Move(param.odrv0)
        
    # Action pour les tests
    lidar.start_motor()
    param.config()
    param.calib()
    move.translation(500)

    # Creation du timer
    timer = RIR_timer((param,move),lidar)

    # Lancement du timer
    timer.start_timer()

    # Attend que les threads se terminent (Bloquant)
    #thread.join()

if __name__ == '__main__':
    main()

