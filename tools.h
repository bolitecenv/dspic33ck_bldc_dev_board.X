#ifndef TOOLS_H
#define TOOLS_H

#include <xc.h> // include processor files - each processor file is guarded.  

static inline uint8_t Scaling100(const uint16_t value, uint16_t value_max, uint16_t target_max) 
{
    return (uint16_t)((uint32_t)(value * target_max) / value_max);
}

#endif /* TOOLS_H */