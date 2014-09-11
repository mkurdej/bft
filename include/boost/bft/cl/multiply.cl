/*
Copyright (c) 2011-2014
Marek Kurdej

Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt
*/

/** Element-wise multiplication */
__kernel void multiply_1d(__global __write_only float* dMult12,
                          __global __read_only const float* dM1,
                          __global __read_only const float* dM2,
                          const __read_only ulong count)
{
    /* Get the index of the current element to be processed */
    uint gid = get_global_id(0);

    if (gid < count) {
        dMult12[gid] = dM1[gid] * dM2[gid];
    }
}
