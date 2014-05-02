#pragma once
#include <util/global.h>
#include "particle.h"
#include "interaction.h"

class TFeynRules
{
public:
    ~TFeynRules()
    {
        for (QSet<TParticle*>::Iterator i = Particles.begin(); i != Particles.end(); i++)
            delete *i;
        for (QSet<TInteraction*>::Iterator i = Interactions.begin(); i != Interactions.end(); i++)
            delete *i;
    }
    
public:
    QSet<TParticle*> Particles;
    QSet<TInteraction*> Interactions;
};
