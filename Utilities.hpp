#pragma once
#include <stddef.h>


/* 
this function assumes that al is a power of 2.
reason for this being reasonable : https://en.cppreference.com/cpp/language/object#Alignment
even though this is about objects, notice that everything else (that is not an object) has size that is a power of 2 anyways.. */
inline constexpr size_t alignedSize(size_t rawSize, size_t al){
    /* to round up to nearest al, we can add al-1 and then round down.
        since al = 2^i for some i:
            rounding down to nearst al multiple is just dscarding all 1's to the left of the ith i.
       
        sifratiot my beloved.
    */
    return (rawSize + (al-1)) & (~(al-1));
}