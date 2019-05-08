#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import serial
import time

arduino = serial.Serial(port, 9600)
rasp_msg = 'b'

while True:
    print(serial.read().decode())
    arduino.write(rasp_msg.encode())
    time.sleep(10)
    