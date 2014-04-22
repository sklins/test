#pragma once
#include "graph_types.h"

class TEdge
{
public:
    friend class TDiagram;
    TEdge(TVertex* a, TVertex* b, TParticle *particle) : A(a), B(b) {Particle = particle;}
    
private:
    //const
    TParticle *Particle;
    TVertex *A;
    TVertex *B;
};
