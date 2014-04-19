#pragma once
#include <util/global.h>
#include "wick_slot.h"

struct TWickEdge
{
    public:
        inline TWickEdge(const TWickSlot* source, const TWickSlot* target, uint32_t particleType)
            : Source(source), Target(target), ParticleType(particleType)
        { }
    
        inline TWickEdge()
            : Source(NULL), Target(NULL), ParticleType(0)
        { }

    
    public:
        const TWickSlot* Source;
        const TWickSlot* Target;
        uint32_t ParticleType;
};
