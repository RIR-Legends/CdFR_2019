#!/usr/bin/env python3
# -*- coding: utf-8 -*-
 
import logging
from logging.handlers import RotatingFileHandler

logging.basicConfig(	filename="rplidar.log", 
						format='%(name)s :: %(asctime)s :: %(levelname)s :: %(message)s', 
						level=logging.DEBUG)
debug = logging.getLogger('Dbg')
data = logging.getLogger('Msg')


file_handler = RotatingFileHandler('data.log', 'a', 1000000, 1)
file_handler.setLevel(logging.DEBUG)
file_handler.setFormatter(logging.Formatter('%(asctime)s :: %(message)s'))
debug.addHandler(file_handler)

stream_handler = logging.StreamHandler()
stream_handler.setLevel(logging.DEBUG)
debug.addHandler(stream_handler)
data.addHandler(stream_handler)

debug.info('Hello')
debug.warning('Testing %s', 'foo')
data.info('Adding text')
