#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Code adapted from https://github.com/SkoltechRobotics/rplidar

import logging
from logging.handlers import RotatingFileHandler
import sys
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
FORCE_SCAN_BYTE = b'\x21'

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

def _b2i(byte):
    '''Converts byte to integer (for Python 2 compatability)'''
    return byte if int(sys.version[0]) == 3 else ord(byte)

def _process_scan(raw):
    '''Processes input raw data and returns measurment data'''
    new_scan = bool(_b2i(raw[0]) & 0b1)
    inversed_new_scan = bool((_b2i(raw[0]) >> 1) & 0b1)
    quality = _b2i(raw[0]) >> 2
    if new_scan == inversed_new_scan:
        raise RPLidarException('New scan flags mismatch')
    check_bit = _b2i(raw[1]) & 0b1
    if check_bit != 1:
        raise RPLidarException('Check bit not equal to 1')
    angle = ((_b2i(raw[1]) >> 1) + (_b2i(raw[2]) << 7)) / 64.
    distance = (_b2i(raw[3]) + (_b2i(raw[4]) << 8)) / 4.
    return new_scan, quality, angle, distance


class RPLidar(object):
    '''Class for communicating with RPLidar rangefinder scanners'''

    def __init__(self, port = '/dev/ttyUSB0', baudrate=115200, timeout=1):
		'''Initilize RPLidar object for communicating with the sensor.'''
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
		logData.addHandler(file_handler)
		stream_handler = logging.StreamHandler()
		stream_handler.setLevel(logging.DEBUG)
		logDbg.addHandler(stream_handler)
		
		self.connect()
		self.start_motor()

    def connect(self):
        '''Connects to the serial port with the name `self.port`. If it was
        connected to another serial port disconnects from it first.'''
        if self._serial_port is not None:
            self.disconnect()
        self.logDbg.info('Connection...')
        try:
            self._serial_port = serial.Serial(
                self.port, self.baudrate,
                parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE,
                timeout=self.timeout, dsrdtr=True)
           self.logDbg.info('Connection done!')
        except serial.SerialException as err:
            self.logDbg.exception('Connection failed : %s' % err)
            raise RPLidarException('Failed to connect to the sensor '
                                   'due to: %s' % err)

    def disconnect(self):
        '''Disconnects from the serial port'''
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
        '''Starts sensor motor'''
        self.logDbg.info('Starting motor...')
        # For A1
        self._serial_port.dtr = False

        # For A2
        self.set_pwm(DEFAULT_MOTOR_PWM)
        self.motor_running = True
        self.logDbg.info('Motor started!')

    def stop_motor(self):
        '''Stops sensor motor'''
        self.logDbg.info('Stopping motor...')
        # For A2
        self.set_pwm(0)
        time.sleep(.001)
        # For A1
        self._serial_port.dtr = True
        self.motor_running = False
        self.logDbg.info('Motor stopped!')

    def _send_payload_cmd(self, cmd, payload):
        '''Sends `cmd` command with `payload` to the sensor'''
        size = struct.pack('B', len(payload))
        req = SYNC_BYTE + cmd + size + payload
        checksum = 0
        for v in struct.unpack('B'*len(req), req):
            checksum ^= v
        req += struct.pack('B', checksum)
        self._serial_port.write(req)
        self.logDbg.debug('Command sent: %s' % req)

    def _send_cmd(self, cmd):
        '''Sends `cmd` command to the sensor'''
        req = SYNC_BYTE + cmd
        self._serial_port.write(req)
        self.logDbg.debug('Command sent: %s' % req)

    def _read_descriptor(self):
        '''Reads descriptor packet'''
        descriptor = self._serial_port.read(DESCRIPTOR_LEN)
        self.logDbg.debug('Received descriptor: %s', descriptor)
        if len(descriptor) != DESCRIPTOR_LEN:
            self.logDbg.exception('In read_descriptor : length mismatch')
            raise RPLidarException('Descriptor length mismatch')
        elif not descriptor.startswith(SYNC_BYTE + SYNC_BYTE2):
            self.logDbg.exception('In read_descriptor : incorrect starting bytes')
            raise RPLidarException('Incorrect descriptor starting bytes')
        is_single = _b2i(descriptor[-2]) == 0
        return _b2i(descriptor[2]), is_single, _b2i(descriptor[-1])

    def _read_response(self, dsize):
        '''Reads response packet with length of `dsize` bytes'''
        self.logDbg.debug('Trying to read response: %d bytes', dsize)
        data = self._serial_port.read(dsize)
        self.logDbg.debug('Received data: %s', data)
        if len(data) != dsize:
            self.logDbg.exception('In read_response : wrong body size')
            raise RPLidarException('Wrong body size')
        return data

    def get_info(self):
        '''Get device information
        Returns
        -------
        dict
            Dictionary with the sensor information
        '''
        self._send_cmd(GET_INFO_BYTE)
        dsize, is_single, dtype = self._read_descriptor()
        if dsize != INFO_LEN:
            self.logDbg.exception('In get_info : wrong reply length')
            raise RPLidarException('Wrong get_info reply length')
        if not is_single:
            self.logDbg.exception('In get_info : not a single response mode')
            raise RPLidarException('Not a single response mode')
        if dtype != INFO_TYPE:
            self.logDbg.exception('In get_info : wrong response data type')
            raise RPLidarException('Wrong response data type')
        raw = self._read_response(dsize)
        serialnumber = codecs.encode(raw[4:], 'hex').upper()
        serialnumber = codecs.decode(serialnumber, 'ascii')
        data = {
            'model': _b2i(raw[0]),
            'firmware': (_b2i(raw[2]), _b2i(raw[1])),
            'hardware': _b2i(raw[3]),
            'serialnumber': serialnumber,
        }
        self.logDbg.info('In get_info : %s' %s)
        return data

    def get_health(self):
        '''Get device health state. When the core system detects some
        potential risk that may cause hardware failure in the future,
        the returned status value will be 'Warning'. But sensor can still work
        as normal. When sensor is in the Protection Stop state, the returned
        status value will be 'Error'. In case of warning or error statuses
        non-zero error code will be returned.
        Returns
        -------
        status : str
            'Good', 'Warning' or 'Error' statuses
        error_code : int
            The related error code that caused a warning/error.
        '''
        self._send_cmd(GET_HEALTH_BYTE)
        dsize, is_single, dtype = self._read_descriptor()
        if dsize != HEALTH_LEN:
            self.logDbg.exception('In get_health : wrong reply length')
            raise RPLidarException('Wrong get_health reply length')
        if not is_single:
            self.logDbg.exception('In get_health : not a single response mode')
            raise RPLidarException('Not a single response mode')
        if dtype != HEALTH_TYPE:
            self.logDbg.exception('In get_health : wrong response data type')
            raise RPLidarException('Wrong response data type')
        raw = self._read_response(dsize)
        status = _HEALTH_STATUS[_b2i(raw[0])]
        error_code = (_b2i(raw[1]) << 8) + _b2i(raw[2])
        return status, error_code

    def clear_input(self):
        '''Clears input buffer by reading all available data'''
        self.logDbg.info('Clearing input buffer')
        self._serial_port.read_all()

    def stop(self):
        '''Stops scanning process, disables laser diode and the measurment
        system, moves sensor to the idle state.'''
        self.logDbg.info('Stop scanning')
        self._send_cmd(STOP_BYTE)
        time.sleep(.001)
        self.clear_input()

    def reset(self):
        '''Resets sensor core, reverting it to a similar state as it has
        just been powered up.'''
        self.logDbg.info('Resetting the sensor')
        self._send_cmd(RESET_BYTE)
        time.sleep(.002)

    def iter_measurments(self, max_buf_meas=500):
        '''Iterate over measurments. Note that consumer must be fast enough,
        otherwise data will be accumulated inside buffer and consumer will get
        data with increaing lag.
        Parameters
        ----------
        max_buf_meas : int
            Maximum number of measurments to be stored inside the buffer. Once
            numbe exceeds this limit buffer will be emptied out.
        Yields
        ------
        new_scan : bool
            True if measurment belongs to a new scan
        quality : int
            Reflected laser pulse strength
        angle : float
            The measurment heading angle in degree unit [0, 360)
        distance : float
            Measured object distance related to the sensor's rotation center.
            In millimeter unit. Set to 0 when measurment is invalid.
        '''
        self.start_motor()
        status, error_code = self.get_health()
        self.logDbg.debug('Health status: %s [%d]', status, error_code)
        if status == _HEALTH_STATUS[2]:
            self.logDbg.warning('Trying to reset sensor due to the error. Error code: %d', error_code)
            self.reset()
            status, error_code = self.get_health()
            if status == _HEALTH_STATUS[2]:
                raise RPLidarException('RPLidar hardware failure. Error code: %d' % error_code)
        elif status == _HEALTH_STATUS[1]:
            self.logDbg.warning('Warning sensor status detected! Error code: %d', error_code)
        cmd = SCAN_BYTE
        self._send_cmd(cmd)
        dsize, is_single, dtype = self._read_descriptor()
			
        if dsize != 5:
            self.logDbg.exception('In measurment : wrong reply length')
            raise RPLidarException('Wrong get_info reply length')
        if is_single:
            self.logDbg.exception('In measurment : not a single response mode')
            raise RPLidarException('Not a multiple response mode')
        if dtype != SCAN_TYPE:
            self.logDbg.exception('In measurment : wrong response data type')
            raise RPLidarException('Wrong response data type')
        while True:
            raw = self._read_response(dsize)
            self.logData.debug('Received scan response: %s' % raw)
            if max_buf_meas:
                data_in_buf = self._serial_port.in_waiting
                if data_in_buf > max_buf_meas*dsize:
                    self.logDbg.warning(
                        'Too many measurments in the input buffer: %d/%d. '
                        'Clearing buffer...',
                        data_in_buf//dsize, max_buf_meas)
                    self._serial_port.read(data_in_buf//dsize*dsize)
            yield _process_scan(raw)

    def iter_scans(self, max_buf_meas=500, min_len=5):
        '''Iterate over scans. Note that consumer must be fast enough,
        otherwise data will be accumulated inside buffer and consumer will get
        data with increasing lag.
        Parameters
        ----------
        max_buf_meas : int
            Maximum number of measurments to be stored inside the buffer. Once
            numbe exceeds this limit buffer will be emptied out.
        min_len : int
            Minimum number of measurments in the scan for it to be yelded.
        Yields
        ------
        scan : list
            List of the measurments. Each measurment is tuple with following
            format: (quality, angle, distance). For values description please
            refer to `iter_measurments` method's documentation.
        '''
        scan = []
        iterator = self.iter_measurments(max_buf_meas)
        for new_scan, quality, angle, distance in iterator:
            if new_scan:
                if len(scan) > min_len:
                    yield scan
                scan = []
            if quality > 0 and distance > 0:
				scan.append((quality, angle, distance))