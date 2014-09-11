/*
Copyright (c) 2011-2014
Marek Kurdej

Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt
*/

#include "GridSize1D.h"

/// Run with at least ```pointCount, gridSizeRadius.size``` threads.
__kernel void create_lidar_grid_2d(
    __global __write_only float* dFree, __global __write_only float* dOccupied,
    __global __write_only float* dOmega,
    __global __read_only const float* dScanAngle,  // [degrees]
    __global __read_only const float* dScanRadius, // [metres]
    const __read_only uint pointCount,
    const __read_only struct GridSize1D gridSizeAngle,  // [degrees]
    const __read_only struct GridSize1D gridSizeRadius, // [metres]
    const __read_only float massFree, const __read_only float massOccupied)
{
    // Get the index of the current element to be processed
    uint gidPoint = get_global_id(0);

    if (gidPoint < pointCount) {
        uint gidRadius = get_global_id(1);
        if (gidRadius >= gridSizeRadius.size) {
            return;
        }

        uint angle = getGridIndex(dScanAngle[gidPoint], gridSizeAngle);
        if (angle < 0 || angle >= gridSizeAngle.size) {
            return;
        }
        uint radius = getGridIndex(dScanRadius[gidPoint], gridSizeRadius);
        if (radius < 0 || radius >= gridSizeRadius.size) {
            return;
        }

        ulong idx = gidRadius * gridSizeAngle.size + angle;

        if (gidRadius < radius) {
            // set mass at obstacle to Free
            dFree[idx] = massFree;
            dOccupied[idx] = 0;
            dOmega[idx] = 1 - massFree;
        } else if (gidRadius == radius) {
            // set mass at obstacle to Occupied
            dFree[idx] = 0;
            dOccupied[idx] = massOccupied;
            dOmega[idx] = 1 - massOccupied;
        } else {
            // set all mass to Omega
            dFree[idx] = 0;
            dOccupied[idx] = 0;
            dOmega[idx] = 1;
        }
    }
}
