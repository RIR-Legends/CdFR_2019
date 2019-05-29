#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math

class Lidar():
    Combi = {	"B1B2" : (1900, 140, 120, 60),
			    "B1B3" : (3242, 140, 120, 60),
			    "B2B3" : (3242, 140, 120, 60),
			    "B1M"  : (1551, 70 , 120, 60),
			    "B2M"  : (2491, 70 , 120, 60),
    			"B3M"  : (1844, 70 , 120, 60)
    } # (distance_moy, tolerance_distance, angle_moy, tolerance_angle)

    def __init__(self):
        ### Initlialiser le LIDAR
        self.Lidar = RIR_rplidar('/dev/ttyUSB0')
        self.scans = self.Lidar.iter_scans()
        
    def stop(self):
        self.Lidar.stop()
        self.Lidar.disconnect()

    def get_RFID(self):
        ### Get last version of scans
        scan = next(self.scans)
        #for scan in self.scans:
        #    pass

        ### Set in trigo
        scan = Lidar.__hor_2_trigo(scan)

        ### Gathering points in obstacles
        RFID = self.__aggregate__(scan)

        ### Determine markers - remove others like people or other robots
        RFID = self.__LM__(RFID)

        ### Convert in meter, radian
        RFID_out = []
        for rfid in RFID:
            RFID_out.append([rfid[0]*0.001, Lidar.__deg_2_rad(rfid[1])])

        ### Return result to SLAM
        return RFID_out

    def __aggregate__(self, measurments):
        # measurment est un tuple de (qualité, distance, angle)
        grp_LM = []

        grp_LM_temp = []
        distance = 0 #Distance entre deux points
        tol_distance = 200 #20cm entre deux points

        # Regroupe les points selon leurs inter-distances
        for m in measurments:
            if len(grp_LM_temp) == 0:
                grp_LM_temp.append(m)
                continue
            for elem in grp_LM_temp:
                distance = math.sqrt(elem[1]**2 + m[1]**2 - 2*elem[1]*m[1]*math.cos(Lidar.__deg_2_rad(elem[2]-m[2])))
                if distance < tol_distance:
                    grp_LM_temp.append(m)
                else:
                    grp_LM.append(LM_temp)
                    grp_LM_temp = [m]

        # Verification début et fin du set, continuité de 360 à 0
        distance = math.sqrt(grp_LM[0][0][1]**2 + grp_LM[-1][-1][1]**2 - 2*grp_LM[0][0][1]*grp_LM[-1][-1][1]*math.cos(Lidar.__deg_2_rad(grp_LM[0][0][2]-grp_LM[-1][-1][2])))
        if distance < tol_distance
            for _ in range(len(grp_LM[-1])):
                grp_LM[0].insert(0, grp_LM[-1].pop())
            grp_LM.pop()

        # Aggrégation des points, en moyenne ou pointe ou autre
        # Methode 1 : moyenne
        # Methode 2 : histogramme, dans chaque set de point, on peut realiser un histogramme avec la distance, puis determiner la forme qui correspond à l'histogramme
        # Methode 3 (utilisé) : point le plus proche dans l'histogramme de chaque, puis comparer les dimensions de tables.
        # Methode 3b : Prendre en compte plus loin avec support central
        LM_major = []
        LM_major_temp = LM[0][0]
        for grp_lm in grp_LM:
            for point in grp_lm:
                if point[1] < LM_major_temp[1]:
                    LM_major_temp = point
            LM_major.append(LM_major_temp)


        return LM_major

    def __LM__(self, RFID):
        diff = (0, 0) # Difference en distance et angle
        common = [[0]*4]*len(RFID)

        for i in range(RFID):
            for j in range(i,RFID):
                diff = (0, math.fabs(RFID[i][2] - RFID[j][2]))
                if diff[1] > 180:
                    diff = (0, diff[1] - 180)
                if diff[1] > 55:
                    diff = (math.sqrt(RFID[i][1]**2 + RFID[j][1]**2 - 2*RFID[i][1]*RFID[j][1]*math.cos(Lidar.__deg_2_rad(diff[1])))
                    if diff[0] > Lidar.Combi["B1B2"][0]-Lidar.Combi["B1B2"][1] and diff[0] > Lidar.Combi["B1B2"][0]+Lidar.Combi["B1B2"][1]
                        common[i][0], common[i][1] = common[i][0] + 1, common[i][1] + 1
                        common[j][0], common[j][1] = common[j][0] + 1, common[j][1] + 1
                        continue
                    if diff[0] > Lidar.Combi["B1B3"][0]-Lidar.Combi["B1B3"][1] and diff[0] > Lidar.Combi["B1B3"][0]+Lidar.Combi["B1B3"][1]
                        common[i][0], common[i][1], common[i][2] = common[i][0] + 1, common[i][1] + 1, common[i][2] + 2
                        common[j][0], common[j][1], common[j][2] = common[j][0] + 1, common[j][1] + 1, common[j][2] + 2
                        continue
                    if diff[0] > Lidar.Combi["B1M"][0]-Lidar.Combi["B1M"][1] and diff[0] > Lidar.Combi["B1M"][0]+Lidar.Combi["B1M"][1]
                        common[i][0], common[i][3] = common[i][0] + 1, common[i][3] + 1
                        common[j][0], common[j][3] = common[j][0] + 1, common[j][3] + 1
                        continue
                    if diff[0] > Lidar.Combi["B2M"][0]-Lidar.Combi["B2M"][1] and diff[0] > Lidar.Combi["B2M"][0]+Lidar.Combi["B2M"][1]
                        common[i][1], common[i][3] = common[i][1] + 1, common[i][3] + 1
                        common[j][1], common[j][3] = common[j][1] + 1, common[j][3] + 1
                        continue
                    if diff[0] > Lidar.Combi["B3M"][0]-Lidar.Combi["B3M"][1] and diff[0] > Lidar.Combi["B3M"][0]+Lidar.Combi["B3M"][1]
                        common[i][2], common[i][3] = common[i][2] + 1, common[i][3] + 1
                        common[j][2], common[j][3] = common[j][2] + 1, common[j][3] + 1
                        continue

        RFID_final = []
        # Tri selon le point qui rassemble le plus de correspondance
        for i in range(len(common)):
            if common[0] >= 2 or common[1] >= 2 or common[2] == 3 or common[3] >= 2:
                RFID_final.append([RFID[i][1], RFID[i][2]])
        return RFID_final

    def get_obstacles(self, step = 30, max_dist = 300, max_err = 5):
        scan = next(self.scans)
        #for scan in self.scans:
        #    pass

        next_angle = 0
        res = []
        scan = Lidar.__hor_2_trigo(scan) # Range les scan par ordre croissant des angles
        for measurement in scan:
            if measurement[1] > next_angle - max_err:
                if measurement[2] < max_dist:
                    res.append(1)
                    next_angle = next_angle + step
                if measurement[1] > next_angle + max_err:
                    res.append(0)
                    next_angle = next_angle + step
        return res

    def __hor_2_trigo(scan):
        return sorted(scan, key=lambda s: s[1])

    def __deg_2_rad(deg):
        return deg*math.pi/180
