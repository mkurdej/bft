#include "cl/set.h"

//==============================================================================
/// Mass function to commonality using Möbius transform 
/// 1D SoA (Structure-of-Arrays)
///
/// Data structure:
///     0000|AAAA|BBBB|OOOO    <- get_global_size(0) elements of each type in a row
__kernel
void mass_to_commonality_1d_soa
    (
        __global __write_only float * dQ,
        __global __read_only const float * dM,
        const __read_only uint setSize,
        const __read_only ulong count
    )
{
    // Get the index of the current element to be processed
    uint gid = get_global_id(0);
    
    if (gid < count) {
        const uint powersetSize = (1 << setSize);
        // Initialize commonality with mass
        for (uint A = 0; A < powersetSize; ++A) {       // for all subsets in powerset 2^FOD
            uint Aidx = A*count + gid;
            dQ[Aidx] = dM[Aidx];
        }
    
        for (uint set = 0; set < setSize; ++set) {      // for all sets in frame of discernement (FOD)
            uint powerset = (1 << set);     // 2^set    // set index in powerset 2^FOD
            for (uint A = 0; A < powersetSize; ++A) {   // for all subsets in powerset 2^FOD
                if(is_subset_of(powerset, A)) {
                    uint B = set_minus(A, powerset);
                    dQ[B*count + gid] += dQ[A*count + gid];
                }
            }
        }
    }
}

//==============================================================================
/// Mass function to commonality using Möbius transform 
/// 1D AoS (Array-of-Structures)
///
/// Data structure:
///     0ABO|0ABO|0ABO|0ABO    <- get_global_size(0) elements of each type in a row
__kernel
void mass_to_commonality_1d_aos
    (
        __global __write_only float * dQ,
        __global __read_only const float * dM,
        const __read_only uint setSize,
        const __read_only ulong count
    )
{
    // Get the index of the current element to be processed
    uint gid = get_global_id(0);

    if (gid < count) {
        const uint powersetSize = (1 << setSize);
        uint base = gid*powersetSize;
    
        // Initialize commonality with mass
        for (uint A = 0; A < powersetSize; ++A) {       // for all subsets in powerset 2^FOD
            dQ[base + A] = dM[base + A];
        }
    
        for (uint set = 0; set < setSize; ++set) {      // for all sets in frame of discernement (FOD)
            uint powerset = (1 << set);     // 2^set    // set index in powerset 2^FOD
            for (uint A = 0; A < powersetSize; ++A) {   // for all subsets in powerset 2^FOD
                if(is_subset_of(powerset, A)) {
                    uint B = set_minus(A, powerset);
                    dQ[base + B] += dQ[base + A];
                }
            }
        }
    }
}

//==============================================================================
/// Commonality function to mass using Möbius transform 
/// 1D SoA (Structure-of-Arrays)
///
/// Data structure:
///     0000|AAAA|BBBB|OOOO    <- get_global_size(0) elements of each type in a row
__kernel
void commonality_to_mass_1d_soa
    (
        __global __write_only float * dM,
        __global __read_only const float * dQ,
        const __read_only uint setSize,
        const __read_only ulong count
    )
{
    // Get the index of the current element to be processed
    uint gid = get_global_id(0);
    
    if (gid < count) {
        const uint powersetSize = (1 << setSize);

        // Initialize commonality with mass
        for (uint A = 0; A < powersetSize; ++A) {       // for all subsets in powerset 2^FOD
            uint Aidx = A*count + gid;
            dM[Aidx] = dQ[Aidx];
        }
    
        for (uint set = 0; set < setSize; ++set) {      // for all sets in frame of discernement (FOD)
            uint powerset = (1 << set);     // 2^set    // set index in powerset 2^FOD
            for (uint A = 0; A < powersetSize; ++A) {   // for all subsets in powerset 2^FOD
                if(is_subset_of(powerset, A)) {
                    uint B = set_minus(A, powerset);
                    dM[B*count + gid] -= dM[A*count + gid];
                }
            }
        }
    }
}

//==============================================================================
/// Commonality function to mass using Möbius transform 
/// 1D AoS (Array-of-Structures)
///
/// Data structure:
///     0ABO|0ABO|0ABO|0ABO    <- get_global_size(0) elements of each type in a row
__kernel
void commonality_to_mass_1d_aos
    (
        __global __write_only float * dM,
        __global __read_only const float * dQ,
        const __read_only uint setSize,
        const __read_only ulong count
    )
{   
    // Get the index of the current element to be processed
    uint gid = get_global_id(0);

    if (gid < count) {
        const uint powersetSize = (1 << setSize);
        uint base = gid*powersetSize;
    
        // Initialize commonality with mass
        for (uint A = 0; A < powersetSize; ++A) {       // for all subsets in powerset 2^FOD
            dM[base + A] = dQ[base + A];
        }
    
        for (uint set = 0; set < setSize; ++set) {      // for all sets in frame of discernement (FOD)
            uint powerset = (1 << set);     // 2^set    // set index in powerset 2^FOD
            for (uint A = 0; A < powersetSize; ++A) {   // for all subsets in powerset 2^FOD
                if(is_subset_of(powerset, A)) {
                    uint B = set_minus(A, powerset);
                    dM[base + B] -= dM[base + A];
                }
            }
        }
    }
}
