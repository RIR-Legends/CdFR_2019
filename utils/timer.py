# -*- coding: utf-8 -*-
#!/usr/bin/env python3

from threading import Thread
import time


def RIR_timer(Motor, Lidar, Communication):
    DepartTime = time.time()
    time.sleep(5)
    Now = time.time() - DepartTime
    while Now < 10:
        time.sleep(.1)
        Now = time.time() - DepartTime
        #print(str(Now)+"\n")
    #STOP ALL HERE

def main():
    # Cr�ation des threads
    launch_timer = threading.Thread(target=RIR_timer, args=(Odrive, RPLidar, Com))

    # Lancement des threads
    thread.start()

    # Attend que les threads se terminent
    ##thread.join()

if __name__ == '__main__':
    main()
