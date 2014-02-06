#pragma once
#include <util/global.h>
#include "wick_slot.h"

struct TWickEdge
{
    public:
        inline TWickEdge(const TWickSlot* source, const TWickSlot* target, uint32_t particleType)
            : Source(source), Target(target), ParticleType(particleType)
        { }

    
    public:
        const TWickSlot* const Source;
        const TWickSlot* const Target;
        uint32_t const ParticleType;
};

