#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Initial source : http://anothermaker.xyz/iot/communication-entre-un-raspberry-pi-et-un-arduino-5319

import serial  # https://pyserial.readthedocs.io/en/latest/pyserial_api.html
import time

    
class Communication():
    MSG = { "Recu" : '1',               "Attente" : '0',            "Action_Finished" : 't',
    
            "Arret" : 'a',              "Initialisation" : 'I',     "Transport" : 'T',
            "Palet_Floor_In" : 'f',     "Palet_Wall_In" : 'w',
            "Palet_Floor_Out" : 'F',    "Palet_Wall_Out" : 'W',
            
            "Tirette" : 'D',            "Violet" : 'v',             "Orange" : 'o',
            "Avancer" : 'a',            "Reculer" : 'r'}

    def __init__(self, port = '/dev/ttyACM0'):
        self.__arduino = serial.Serial(port, 9600)
        self.__ard_msg = ""
        self.__rasp_msg = Communication.MSG["Attente"]
        
        self.readyNext = True
        self.Tirette = True
        self.OrangeSide = None
        self.Avancer = False
        self.Reculer = False
        
        #self.__arduino.flushInput()
        
    def send(self,msg):
        self.__rasp_msg = msg
        self.readyNext = False
        if msg == Communication.MSG["Action_Finished"]:
            self.Avancer = False
            self.Reculer = False
        
        while self.__ard_msg != Communication.MSG["Recu"]:
            self.__arduino.write(self.__rasp_msg.encode())
            try:
                self.__ard_msg = self.__arduino.read().decode()
            except:
                self.__ard_msg = Communication.MSG["Attente"]
            time.sleep(.5)
            
        self.__rasp_msg = Communication.MSG["Attente"]
        self.__arduino.write(self.__rasp_msg.encode())
    
    def read(self, print_rep = False):
        #self.__arduino.flushInput()
        #time.sleep(1)
        try:
            self.__ard_msg = self.__arduino.read().decode()
        except:
            self.__ard_msg = Communication.MSG["Attente"]
        if print_rep:
            print(self.__ard_msg)
        if (self.__ard_msg == Communication.MSG["Attente"] or self.__ard_msg == Communication.MSG["Recu"]):
            return
        self.__interpreter(self.__ard_msg)
        
        self.__rasp_msg = Communication.MSG["Recu"]
        self.__arduino.write(self.__rasp_msg.encode())
            
    def __interpreter(self,msg):
        if msg == Communication.MSG["Tirette"]:
            self.Tirette = False
        
        if msg == Communication.MSG["Action_Finished"]:
            self.readyNext = True
            
        if msg == Communication.MSG["Orange"]:
            self.OrangeSide = True
        elif msg == Communication.MSG["Violet"]:
            self.OrangeSide = False
            
        if msg == Communication.MSG["Avancer"]:
            self.Avancer = True
        elif msg == Communication.MSG["Reculer"]:
            self.Reculer = True
    
    
    
    
def test():
    com = Communication('COM5')
    
    print("Waiting side...")
    while com.OrangeSide == None:
        com.read(True)
    side = "violet"
    if com.OrangeSide:
        side = "orange"
    print("Side is {}\n" .format(side))
    time.sleep(10)
    
    print("Waiting tirette...")
    while com.Tirette:
        com.read(True)
    print("Let's Go!!\n")
    time.sleep(10)
    
    print("Trying one action now.")
    com.send(Communication.MSG["Transport"])
    while not com.readyNext:
        com.read(True)
    print("Job is done.\n")
    time.sleep(5)
    
    print("Turn off robot...")
    com.send(Communication.MSG["Arret"])
    
if __name__ == '__main__':
    test()
