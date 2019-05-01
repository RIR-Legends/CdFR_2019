#!/usr/bin/env python3
'''Records scans to a given file in the form of numpy array.
Usage example:

$ ./record_scans.py out.npy'''
import sys
import numpy as np
from RIR_rplidar import RPLidar


PORT_NAME = '/dev/ttyUSB0'


def run(path):
    '''Main function'''
    lidar = RPLidar(PORT_NAME)
    data = []
    try:
        print('Recording measurments... Press Crl+C to stop.')
        for scan in lidar.scan():
            data.append(np.array(scan))
    except KeyboardInterrupt:
        print('Stopping.')
    lidar.stop()
    lidar.disconnect()
    np.savetxt(path, np.array(data))

if __name__ == '__main__':
    run("test.txt")
