#pragma once
#include "graph_types.h"

class TEdge
{
public:
    friend class TDiagram;
    TEdge(TVertex* a, TVertex* b) : A(a), B(b) {}
    
private:
    TVertex *A;
    TVertex *B;
};
