#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Initial source : http://anothermaker.xyz/iot/communication-entre-un-raspberry-pi-et-un-arduino-5319

import serial  # https://pyserial.readthedocs.io/en/latest/pyserial_api.html

class Communication():
    MSG = { "Recu" : '1',               "Attente" : '0',            "Action_Finished" : 't',

            "Arret" : 'a',              "Initialisation" : 'I',     "Transport" : 'T',
            "Palet_Floor_In" : 'f',     "Palet_Wall_In" : 'w',
            "Palet_Floor_Out" : 'F',    "Palet_Wall_Out" : 'W',

            "Tirette" : 'D',            "Violet" : 'v',             "Orange" : 'o',
            "Avancer" : 'a',            "Reculer" : 'r'}

    def __init__(self, port = '/dev/ttyASC0'):
        self.__arduino = serial.Serial(port, 9600)
        self.__ard_msg = ""
        self.__rasp_msg = Communication.MSG["Attente"]

        self.readyNext = True
        self.Tirette = True
        self.OrangeSide = None
        self.Avancer = False
        self.Reculer = False

        self.__arduino.flushInput()

    def send(self,msg):
        self.__rasp_msg = msg
        self.readyNext = False
        if msg == Communication.MSG["Action_Finished"]:
            self.Avancer = False
            self.Reculer = False

        while self.__ard_msg != Communication.MSG["Recu"]:
            self.__arduino.write(self.__rasp_msg)
            self.__ard_msg = self.__arduino.readline()
        self.__rasp_msg = Communication.MSG["Attente"]
        for i in range(1000):
            self.__arduino.write(self.__rasp_msg)

    def read(self, print_rep = False):
        while self.__ard_msg == Communication.MSG["Attente"] or self.__ard_msg == Communication.MSG["Recu"]:
            self.__ard_msg = self.__arduino.readline()
        self.__interpreter(self.__ard_msg)

        self.__rasp_msg = Communication.MSG["Recu"]
        while self.__arduino.readline() != Communication.MSG["Attente"] or self.__arduino.readline() != Communication.MSG["Recu"]:
            self.__arduino.write(self.__rasp_msg)

        if print_rep:
            print(Communication.MSG[self.__ard_msg])

    def check(self):
        self.__arduino.write(Communication.MSG["Attente"])
        return self.__arduino.readline() != Communication.MSG["Recu"] and self.__arduino.readline() != Communication.MSG["Attente"]

    def checkAndRead(self, print_rep = False):
        if self.check():
            self.read()
            return True
        return False

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
    com = Communication()

    print("Waiting side...")
    while com.OrangeSide == None:
        com.checkAndRead(True)
    side = "violet"
    if OrangeSide:
        side = "orange"
    print("Side is {}\n" .format(side))

    print("Waiting tirette...")
    while com.Tirette:
        com.checkAndRead(True)
    print("Let's Go!!\n\n")

    print("Trying one action now.")
    com.send(Communication.MSG["Transport"])
    while not com.readyNext:
        com.checkAndRead(True)
    print("Job is done.\n")

    print("Turn off robot...")
    com.send(Communication.MSG["Arret"])

if __name__ == '__main__':
    test()
