#ifndef TOOLS_H
#define TOOLS_H

#include <xc.h> // include processor files - each processor file is guarded.  

static inline uint16_t Scaling100(const uint16_t value, uint32_t value_max, uint32_t target_max) 
{
    return (uint16_t)((value * target_max) / value_max);
}

#endif /* TOOLS_H */