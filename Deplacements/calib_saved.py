#!/usr/bin/env python3

from __future__ import print_function
import odrive
from odrive.enums import *  # a checker

odrv0 = odrive.find_any()

odrv0.axis0.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
odrv0.axis1.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
while self.odrv0.axis0.current_state != 1 and self.odrv0.axis1.current_state != 1:
    time.sleep(0.1)
odrv0.axis0.motor.config.pre_calibrated = True
odrv0.axis1.motor.config.pre_calibrated = True
ordv0.save_configuration()
