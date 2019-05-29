#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from Robot import Robot

def main(lancer_exp = True):
    robot = Robot(lancer_exp)



if __name__ == '__main__':
    if len(sys.argv) == 1:
        main(sys.argv[1])
    main(True)

