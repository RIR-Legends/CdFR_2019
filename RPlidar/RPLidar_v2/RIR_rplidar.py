#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Code adapted from https://github.com/SkoltechRobotics/rplidar

import logging
from logging.handlers import RotatingFileHandler
import time
import codecs
import serial
import struct

SYNC_BYTE = b'\xA5'
SYNC_BYTE2 = b'\x5A'

GET_INFO_BYTE = b'\x50'
GET_HEALTH_BYTE = b'\x52'

STOP_BYTE = b'\x25'
RESET_BYTE = b'\x40'

SCAN_BYTE = b'\x20'
#FORCE_SCAN_BYTE = b'\x21'

DESCRIPTOR_LEN = 7
INFO_LEN = 20
HEALTH_LEN = 3

INFO_TYPE = 4
HEALTH_TYPE = 6
SCAN_TYPE = 129

#Constants & Command to start A2 motor
MAX_MOTOR_PWM = 1023
DEFAULT_MOTOR_PWM = 660
SET_PWM_BYTE = b'\xF0'

_HEALTH_STATUS = {
    0: 'Good',
    1: 'Warning',
    2: 'Error',
}

logging.basicConfig(	filename="rplidar.log", 
						format='%(name)s :: %(asctime)s :: %(levelname)s :: %(message)s', 
						level=logging.DEBUG)
						
class RPLidarException(Exception):
    '''Basic exception class for RPLidar'''

def _process_scan(raw, log):
    '''Processes input raw data and returns measurment data'''
    new_scan = bool(raw[0] & 0b1)
    inversed_new_scan = bool((raw[0] >> 1) & 0b1)
    quality = raw[0] >> 2
    if new_scan == inversed_new_scan:
        raise RPLidarException('New scan flags mismatch')
    check_bit = _raw[1] & 0b1
    if check_bit != 1:
        raise RPLidarException('Check bit not equal to 1')
    angle = ((raw[1] >> 1) + (raw[2] << 7)) / 64.
    distance = (raw[3] + (raw[4] << 8)) / 4.
    log.debug('Received scan response: {0} (new scan), {1} (quality), {2} (angle), {3} (distance)'.format(new_scan,quality,angle,distance))
    return new_scan, quality, angle, distance


class RPLidar(object):

    def __init__(self, port = '/dev/ttyUSB0', baudrate=115200, timeout=1):
        self._serial_port = None
        self.port = port
        self.baudrate = baudrate
        self.timeout = timeout
        self.motor_running = None
        
        self.logDbg = logging.getLogger('Debug')
        self.logData = logging.getLogger('Data')
        file_handler = RotatingFileHandler('data.log', 'a', 1000000, 1)
        file_handler.setLevel(logging.DEBUG)
        file_handler.setFormatter(logging.Formatter('%(asctime)s :: %(message)s'))
        self.logData.addHandler(file_handler)
        stream_handler = logging.StreamHandler()
        stream_handler.setLevel(logging.DEBUG)
        self.logDbg.addHandler(stream_handler)
        
        self.connect()

    def __exception(self,msg):
        self.logDbg.exception(msg)
        print("Error in RPLidar, check logs")
        raise RPLidarException('')
        
    def connect(self):
        if self._serial_port is not None:
            self.disconnect()
            
        self.logDbg.info('Connecting to RPLidar...')
        try:
            self._serial_port = serial.Serial(
                self.port, self.baudrate,
                parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE,
                timeout=self.timeout, dsrdtr=True)
            self.logDbg.info('Connection done!')
        except serial.SerialException as err:
            self.__exception('Connection issue. Error : {}'.format(err))

    def disconnect(self):
        self.logDbg.info('Disconnection...')
        if self._serial_port is None:
            self.logDbg.info('No disconnection to do.')
            return
            
        self._serial_port.close()
        self.logDbg.info('Disconnection done!')

    def set_pwm(self, pwm):
        assert(0 <= pwm <= MAX_MOTOR_PWM)
        payload = struct.pack("<H", pwm)
        self._send_payload_cmd(SET_PWM_BYTE, payload)

    def start_motor(self):
        self.logDbg.info('Starting motor...')
        # For A1
        #self._serial_port.dtr = False

        # For A2
        self.set_pwm(DEFAULT_MOTOR_PWM)
        
        self.motor_running = True
        self.logDbg.info('Motor started!')

    def stop_motor(self):
        self.logDbg.info('Stopping motor...')
        # For A2
        self.set_pwm(0)
        time.sleep(.001)
        # For A1
        #self._serial_port.dtr = True
        
        self.motor_running = False
        self.logDbg.info('Motor stopped!')

    def stop(self):
        '''Stops scanning process, disables laser diode and the measurment
        system, moves sensor to the idle state.'''
        self.logDbg.info('Stop scanning')
        self._send_cmd(STOP_BYTE)
        time.sleep(.001)
        self.stop_motor()
        self.clear_input()

    def clear_input(self):
        self.logDbg.info('Clearing input buffer')
        self._serial_port.read_all()
        
    def reset(self):
        '''Resets sensor core, reverting it to a similar state as it has
        just been powered up.'''
        self.logDbg.info('Resetting the sensor')
        self._send_cmd(RESET_BYTE)
        time.sleep(.002)        
        
        
    def _send_payload_cmd(self, cmd, payload):
        size = struct.pack('B', len(payload))
        req = SYNC_BYTE + cmd + size + payload
        checksum = 0
        for v in struct.unpack('B'*len(req), req):
            checksum ^= v
        req += struct.pack('B', checksum)
        self._serial_port.write(req)

    def _send_cmd(self, cmd):
        req = SYNC_BYTE + cmd
        self._serial_port.write(req)
        
    def _read_descriptor(self):
        descriptor = self._serial_port.read(DESCRIPTOR_LEN)
        if len(descriptor) != DESCRIPTOR_LEN or not descriptor.startswith(SYNC_BYTE + SYNC_BYTE2):
            self.__exception("Reading descriptor issue.")
        is_single = descriptor[-2] == 0
        return descriptor[2], is_single, descriptor[-1]

    def _read_response(self, dsize):
        data = self._serial_port.read(dsize)
        if len(data) != dsize:
            self.__exception("Response read issue. Wrong body size")
        return data


    def get_info(self):
        self._send_cmd(GET_INFO_BYTE)
        dsize, is_single, dtype = self._read_descriptor()
        if dsize != INFO_LEN or not is_single or dtype != INFO_TYPE:
            self.__exception('Descriptor of device information issue.')
            
        raw = self._read_response(dsize)
        serialnumber = codecs.encode(raw[4:], 'hex').upper()
        serialnumber = codecs.decode(serialnumber, 'ascii')
        data = {
            'model': raw[0],
            'firmware': (raw[2], raw[1]),
            'hardware': raw[3],
            'serialnumber': serialnumber,
        }
        self.logDbg.info('In get_info : %s' %s)
        return data

    def get_health(self):
        self._send_cmd(GET_HEALTH_BYTE)
        dsize, is_single, dtype = self._read_descriptor()
        if dsize != HEALTH_LEN or not is_single or dtype != HEALTH_TYPE:
            self.__exception('Descriptor of health issue.')
            
        raw = self._read_response(dsize)
        status = _HEALTH_STATUS[raw[0]]
        error_code = (raw[1] << 8) + raw[2]
        return status, error_code

    def __check_informations(self):
        status, error_code = self.get_health()
        if status != _HEALTH_STATUS[0]:
            self.reset()
            status, error_code = self.get_health()
            if status != _HEALTH_STATUS[0]:
                self.__exception('Health issue. Error code: {}'.format(error_code))
                
        self._send_cmd(SCAN_BYTE)
        dsize, is_single, dtype = self._read_descriptor()
        if dsize != 5 or is_single or dtype != SCAN_TYPE:
            self.__exception('Descriptor of scan issue.')
        self.logDbg.info('Health and Descriptor are fine')


    def measure(self, buff = 1000):
        while True:
            raw = self._read_response(dsize)
            data_in_buf = self._serial_port.in_waiting
            if data_in_buf > max_buf_meas*dsize:
                self.logDbg.warning("Too many measurments {}/{}. Emptying buffer.".format(data_in_buf//dsize, max_buf_meas))
                self._serial_port.read(data_in_buf//dsize*dsize)
            yield _process_scan(raw,self.logData)
    
    def scan(self, buff = 1000, min_sample = 15):
        self.start_motor()
        self.__check_informations()
        
        scan = []
        itr = self.measure(buff)
        for new_scan, quality, angle, distance in itr:
            if new_scan:
                if len(scan) > min_sample:
                    yield scan
                self.__check_informations()
                scan = []
            if quality > 0 and distance > 0:
                scan.append((quality, angle, distance))
