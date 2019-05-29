# -*- coding: utf-8 -*-
#!/usr/bin/env python3

import threading
import time

class RIR_timer():
    #def __init__(self, Communication, Moteur, Lidar):
    def __init__(self, Lidar):
        self.launcher = threading.Thread(target=self.__RIR_timer, args=(Lidar,))

    def __RIR_timer(self, lidar):
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
    
    def start_timer(self):
        self.launcher.start()

def main():
    import sys
    sys.path.append('../')
    from Deplacement.SLAM.RIR_rplidar import RPLidar

    # Ce qui est lancé avant
    lidar = RPLidar('/dev/ttyUSB0')
    lidar.start_motor()

    # Creation du timer
    timer = RIR_timer(lidar)

    # Lancement du timer
    timer.start_timer()

    # Attend que les threads se terminent (Bloquant)
    #thread.join()

if __name__ == '__main__':
    main()

