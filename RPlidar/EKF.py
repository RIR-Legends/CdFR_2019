#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Code adapted from https://github.com/AtsushiSakai/PythonRobotics
# Initial author : Atsushi Sakai (@Atsushi_twi)

### A faire
# Transition de xEst, PEst, xTrue dans chaque fonction. Retirer des paramètres. Attention aux origines
# Add option RFID in "__init__"

##import sys
##sys.path.append('../')

import sys
import math
import numpy as np

from point import Point


class EKF():
    def __init__(self, err_obs_dist = 0.36, err_obs_ang = 1.0, 
                 err_mot_dist = 0.01, err_mot_ang = 5.0, 
                 max_obs_dist = 20.0, mahalanobis_dist = 2.0):  
        # EKF state covariance
        self.__Cx = np.diag([0.5, 0.5, np.deg2rad(30.0)])**2 # ???

        #  Simulation parameter
        self.__Qsim = np.diag([err_obs_dist, np.deg2rad(err_obs_ang)])**2 # Observation error in distance (m) and angle (deg) [MAX]
        self.__Rsim = np.diag([err_mot_dist, np.deg2rad(err_mot_ang)])**2 # Motion error in distance (m) and angle (deg) (deviation) [MAX]
        
        self.__MAX_RANGE = max_obs_dist  # maximum observation range
        
        self.__M_DIST_TH = mahalanobis_dist  # Threshold of Mahalanobis distance for data association.
        # Tolerance entre landmarks, 
        # Si trop petit, trop de creation de landmarks
        # Si trop grand, position landmarks imprecise
        # Suffisament petit sans rajouter de landmarks lors des tests
        self.__STATE_SIZE = 3  # State size [x,y,yaw]
        self.__LM_SIZE = 2  # LM state size [x,y]
        # RFID positions [x, y]
        self.RFID = np.array([[10.0, -2.0],
                              [15.0, 10.0],
                              [3.0, 15.0],
                              [-5.0, 20.0]])

        # State Vector [x y yaw v]'
        self.xEst = np.zeros((self.__STATE_SIZE, 1))
        self.xTrue = np.zeros((self.__STATE_SIZE, 1))
        self.__PEst = np.eye(self.__STATE_SIZE)

    def __ekf_slam(self, xEst, PEst, u, z):
        # Predict
        S = self.__STATE_SIZE
        xEst[0:S] = self.__motion_model(xEst[0:S], u)
        G, Fx = self.__jacob_motion(xEst[0:S], u)
        PEst[0:S, 0:S] = G.T * PEst[0:S, 0:S] * G + Fx.T * self.__Cx * Fx

        # Update
        for iz in range(len(z[:, 0])):  # for each observation
            minid = self.__search_correspond_LM_ID(xEst, PEst, z[iz, 0:2])

            nLM = self.__calc_n_LM(xEst)
            if minid == nLM:
                print("New LM")
                # Extend state and covariance matrix
                xAug = np.vstack((xEst, self.__calc_LM_Pos(xEst, z[iz, :])))
                PAug = np.vstack((np.hstack((PEst, np.zeros((len(xEst), self.__LM_SIZE)))),
                                np.hstack((np.zeros((self.__LM_SIZE, len(xEst))), np.eye(2)))))
                xEst = xAug
                PEst = PAug
            lm = self.__get_LM_Pos_from_state(xEst, minid)
            y, S, H = self.__calc_innovation(lm, xEst, PEst, z[iz, 0:2], minid)
    
            K = (PEst @ H.T) @ np.linalg.inv(S)
            xEst = xEst + (K @ y)
            PEst = (np.eye(len(xEst)) - (K @ H)) @ PEst
    
        xEst[2] = EKF.__pi_2_pi(xEst[2])
    
        return xEst, PEst

    def __observation(self, xTrue, uDT, RFID, simulation = False):
        xTrue = self.__motion_model(xTrue, uDT)
    
        # add noise to gps x-y
        z = np.zeros((0, 3))
    
        for i in range(len(RFID[:, 0])):
            dx = RFID[i, 0] - xTrue[0, 0]
            dy = RFID[i, 1] - xTrue[1, 0]
            d = math.sqrt(dx**2 + dy**2)
            angle = EKF.__pi_2_pi(math.atan2(dy, dx) - xTrue[2, 0])
            if simulation: 
                if d <= self.__MAX_RANGE:
                    dn = d + np.random.randn() * self.__Qsim[0, 0]  # add noise
                    anglen = angle + np.random.randn() * self.__Qsim[1, 1]  # add noise
                    zi = np.array([dn, anglen, i])
                    z = np.vstack((z, zi))
            else: # Bruit deja present
                z = np.vstack((z, np.array([d, angle, i])))
    
        # add noise to input
        if simulation: 
            ud = np.array([[
                uDT[0, 0] + np.random.randn() * self.__Rsim[0, 0],
                uDT[1, 0] + np.random.randn() * self.__Rsim[1, 1]]]).T
        else:
            ud = np.array([[uDT[0, 0], uDT[1, 0]]]).T
    
        return xTrue, z, ud
     
    def estimate(self, movement, RFID = [], simulation = False):
        '''
        movement : Point
        RFID : Liste de Point
        '''
        
        if len(RFID) == 0:
            RFID = self.RFID
        if type(RFID) != type(np.array(0)):
            RFID = EKF.__load_RFID(RFID)
        
        if movement.hypo == 0:
            movement.set_parcour()
        
        uDT = np.array([[movement.hypo, movement.theta]]).T # Movement in m and rad (only parameter to update)
        self.xTrue, z, ud = self.__observation(self.xTrue, uDT, RFID, simulation)
        self.xEst, self.__PEst = self.__ekf_slam(self.xEst, self.__PEst, ud, z)
        #x_state = self.xEst[0:self.__STATE_SIZE] #(x,y,yaw) estimation of the robot
        return Point(self.xEst[0,0],self.xEst[1,0],self.xEst[2,0])
    
    def __motion_model(self, x, uDT):
        F = np.array([[1.0, 0, 0],
                    [0, 1.0, 0],
                    [0, 0, 1.0]])
    
        B = np.array([[uDT[0, 0] * math.cos(x[2, 0])],
                    [uDT[0, 0] * math.sin(x[2, 0])],
                    [uDT[1, 0]]])
    
        x = (F @ x) + B
        return x

    def __calc_n_LM(self, x):
        n = int((len(x) - self.__STATE_SIZE) / self.__LM_SIZE)
        return n
        
    def __jacob_motion(self, x, u):
        Fx = np.hstack((np.eye(self.__STATE_SIZE), np.zeros(
            (self.__STATE_SIZE, self.__LM_SIZE * self.__calc_n_LM(x)))))
    
        jF = np.array([[0.0, 0.0, -u[0] * math.sin(x[2, 0])],
                    [0.0, 0.0, u[0] * math.cos(x[2, 0])],
                    [0.0, 0.0, 0.0]])
    
        G = np.eye(self.__STATE_SIZE) + Fx.T * jF * Fx
    
        return G, Fx,

    def __calc_LM_Pos(self, x, z):
        zp = np.zeros((2, 1))
    
        zp[0, 0] = x[0, 0] + z[0] * math.cos(x[2, 0] + z[1])
        zp[1, 0] = x[1, 0] + z[0] * math.sin(x[2, 0] + z[1])
    
        return zp

    def __get_LM_Pos_from_state(self, x, ind):
        lm = x[self.__STATE_SIZE + self.__LM_SIZE * ind: self.__STATE_SIZE + self.__LM_SIZE * (ind + 1), :]
    
        return lm

    def __search_correspond_LM_ID(self, xAug, PAug, zi):
        """
        Landmark association with Mahalanobis distance
        """
    
        nLM = self.__calc_n_LM(xAug)
    
        mdist = []
    
        for i in range(nLM):
            lm = self.__get_LM_Pos_from_state(xAug, i)
            y, S, H = self.__calc_innovation(lm, xAug, PAug, zi, i)
            mdist.append(y.T @ np.linalg.inv(S) @ y)
    
        mdist.append(self.__M_DIST_TH)  # new landmark
    
        minid = mdist.index(min(mdist))
    
        return minid

    def __calc_innovation(self, lm, xEst, PEst, z, LMid):
        delta = lm - xEst[0:2]
        q = (delta.T @ delta)[0, 0]
        zangle = math.atan2(delta[1, 0], delta[0, 0]) - xEst[2, 0]
        zp = np.array([[math.sqrt(q), EKF.__pi_2_pi(zangle)]])
        y = (z - zp).T
        y[1] = EKF.__pi_2_pi(y[1])
        H = self.__jacobH(q, delta, xEst, LMid + 1)
        S = H @ PEst @ H.T + self.__Cx[0:2, 0:2]
    
        return y, S, H
    
    def __jacobH(self, q, delta, x, i):
        sq = math.sqrt(q)
        G = np.array([[-sq * delta[0, 0], - sq * delta[1, 0], 0, sq * delta[0, 0], sq * delta[1, 0]],
                    [delta[1, 0], - delta[0, 0], - 1.0, - delta[1, 0], delta[0, 0]]])
    
        G = G / q
        nLM = self.__calc_n_LM(x)
        F1 = np.hstack((np.eye(3), np.zeros((3, 2 * nLM))))
        F2 = np.hstack((np.zeros((2, 3)), np.zeros((2, 2 * (i - 1))),
                        np.eye(2), np.zeros((2, 2 * nLM - 2 * i))))
    
        F = np.vstack((F1, F2))
    
        H = G @ F
    
        return H
    
    def __pi_2_pi(angle):
        return (angle + math.pi) % (2 * math.pi) - math.pi
        
    def __load_RFID(RFID_input):
        RFID = []
        if type(RFID_input[0]) == type(Point(0,0,0)):
            for rfid in RFID_input:
                RFID.append(rfid.x, rfid.y)
        elif type(RFID_input[0]) == type([]):
            RFID = RFID_input
        return np.array(RFID)
            

def simulation(iterations):
    show_animation = True

    slam = EKF()

    # history
    hxEst = slam.xEst
    hxTrue = slam.xTrue

    for _ in range(int(iterations)):
        uDT = Point(0,0,np.random.randn())
        uDT.hypo = np.random.randn()
        x_state = slam.estimate(movement = uDT, RFID = [], simulation = True)        # SEULE LIGNE IMPORTANTE
        x_state = [[x_state.x],[x_state.y],[x_state.theta]]
        
        
        
        # Affichage graphique
        if show_animation:
            import matplotlib.pyplot as plt

        # store data history
        hxEst = np.hstack((hxEst, x_state))
        hxTrue = np.hstack((hxTrue, slam.xTrue))

        if show_animation:  # pragma: no cover
            plt.cla()

            plt.plot(slam.RFID[:, 0], slam.RFID[:, 1], "*k")
            plt.plot(slam.xEst[0], slam.xEst[1], ".r")

            # plot landmark
            n_LM = int((len(slam.xEst) - 3.0) / 2.0)
            for i in range(n_LM):
                plt.plot(slam.xEst[3 + i * 2],
                         slam.xEst[3 + i * 2 + 1], "xg")

            plt.plot(hxTrue[0, :],
                     hxTrue[1, :], "-b")
            plt.plot(hxEst[0, :],
                     hxEst[1, :], "-r")
            plt.axis("equal")
            plt.grid(True)
            plt.pause(0.001)
    

if __name__ == '__main__':
    simulation(sys.argv[1])
