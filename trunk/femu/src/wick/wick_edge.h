#pragma once
#include <util/global.h>
#include "wick_slot.h"

struct TWickEdge
{
    public:
        inline TWickEdge(int source, int target, TParticle* particleType)
            : Source(source), Target(target), ParticleType(particleType)
        { }
    
        inline TWickEdge()
            : Source(0), Target(0), ParticleType(NULL)
        { }

    
    public:
        int Source; // Index in TWickTask::Slots array
        int Target; // Index in TWickTask::Slots array
        TParticle* ParticleType;
};
