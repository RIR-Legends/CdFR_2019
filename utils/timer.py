# -*- coding: utf-8 -*-
#!/usr/bin/env python3

from threading import Thread
import time

class NinetySec(Thread):
    def __init__(self):
        Thread.__init__(self)

    def run(self):
        DepartTime = time.time()
        time.sleep(85)
        Now = time.time() - DepartTime
        while Now < 90:
            time.sleep(.1)
            Now = time.time() - DepartTime
            #print(str(Now)+"\n")
        #STOP ALL HERE

def main():
    # Création des threads
    thread = NinetySec()
    
    # Lancement des threads
    thread.start()
    
    # Attend que les threads se terminent
    thread.join()
    
if __name__ == '__main__':
    main()