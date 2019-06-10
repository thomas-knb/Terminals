#!/usr/bin/python
# -*- coding: utf-8 -*-

from __future__ import print_function
from __future__ import division
from __future__ import absolute_import
import rbfopt
import numpy as np
import math


def obj_funct(l):

    Y = np.array([
        [1, 0, 0, 0, 0, 0],
        [1, 0, 0, 0, 0, 0],
        [0, 1, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0],
        [0, 0, 0, 0, 0, 1],
        [0, 0, 1, 0, 0, 0],
        [0, 0, 0, 1, 0, 0],
        [0, 0, 0, 0, 0, 1]])

    Z = np.array([
        [0, 1, 0, 0, 0, 0],
        [0, 0, 1, 0, 0, 0],
        [0, 0, 0, 1, 0, 0],
        [0, 0, 0, 0, 1, 0],
        [0, 0, 0, 0, 0, 1],
        [0, 0, 0, 0, 0, 0]])

    zt = np.array([
        [1+math.sqrt(2), 1],
        [1, 1+math.sqrt(2)],
        [-1, 1+math.sqrt(2)],
        [-1-math.sqrt(2), 1],
        [-1-math.sqrt(2), -1],
        [-1, -1-math.sqrt(2)],
        [1, -1-math.sqrt(2)],
        [1+math.sqrt(2), -1]])

    # "déclaration" des centres
    x = np.array([[0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0]])

    # calcul de x_1
    x[0] = l[0]*zt[0] + (1-l[0])*zt[1]

    # calcul de (x_2,...,x_5)
    for i in range(1, 5):
        for k1 in range(8):
            x[i] += l[i] * Y[k1][i] * zt[k1]
        for k2 in range(6):
            x[i] += (1-l[i]) * Z[k2][i] * x[k2]

    # calcul de x_6
    for k3 in range(7):
        x[5] += l[5] * Y[k3][5] * zt[k3]
    for k4 in range(6):
        x[5] += (1-l[5]) * Z[k4][5] * x[k4]

    # calcul de la valeur de la fonction objectif
    res = 0
    for p1 in range(8):
        for q1 in range(6):
            res += Y[p1][q1] * math.sqrt(math.pow(x[q1][0] - zt[p1][0], 2) + math.pow(x[q1][1] - zt[p1][1], 2))
    for p2 in range(6):
        for q2 in range(6):
            res += Z[p2][q2] * math.sqrt(math.pow(x[q2][0] - x[p2][0], 2) + math.pow(x[q2][1] - x[p2][1], 2))

    return res


bb = rbfopt.RbfoptUserBlackBox(6, np.array([0] * 6), np.array([1] * 6), np.array(['R', 'R', 'R', 'R', 'R', 'R']), obj_funct)
settings = rbfopt.RbfoptSettings(max_evaluations=50)
alg = rbfopt.RbfoptAlgorithm(settings, bb)
objval, x, itercount, evalcount, fast_evalcount = alg.optimize()

