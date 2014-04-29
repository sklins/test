#pragma once
#include <util/global.h>
#include "wick_slot.h"

struct TWickEdge
{
    public:
        inline TWickEdge(const TWickSlot* source, const TWickSlot* target, TParticle* particleType)
            : Source(source), Target(target), ParticleType(particleType)
        { }
    
        inline TWickEdge()
            : Source(NULL), Target(NULL), ParticleType(NULL)
        { }

    
    public:
        const TWickSlot* Source;
        const TWickSlot* Target;
        TParticle* ParticleType;
};
