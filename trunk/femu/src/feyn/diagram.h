#pragma once
#include <util/global.h>
#include "edge.h"
#include "vertex.h"

class TDiagram
{
    public:
        ~TDiagram ();
    public:
        TVertex* AddInteractionVertex();
        TVertex* AddCorrelationVertex();
        TEdge* AddEdge(TVertex* a, TVertex* b);
        void RemoveEdge(TEdge* e);
        void RemoveVertex(TVertex* x); // должна удалить все инцидентные ребра
    
    private:
        QSet<TEdge*> Edges;
        QSet<TVertex*> Interactions;
        QSet<TVertex*> Correlations;
};
