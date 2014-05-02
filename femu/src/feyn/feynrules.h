#pragma once
#include <util/global.h>

class TFeynRules
{
public:
    ~TFeynRules()
    {
        //ЧТО ЕМУ НЕ НРАВИТСЯ НЕ ПОЙМУ
        qDeleteAll(Particles);
        qDeleteAll(Interactions);
    }
    
public:
    QSet<TParticle*> Particles;
    QSet<TInteraction*> Interactions;
};
