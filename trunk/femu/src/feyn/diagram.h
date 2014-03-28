#pragma once
#include <util/global.h>
#include "edge.h"
#include "vertex.h"

class TDiagram
{
    public:
        ~TDiagram ();
    
    private:
        QSet<TEdge*> Edges;
        QSet<TVertex*> Interactions;
        QSet<TVertex*> Correlations;
};
