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
        void RemoveVertex(TVertex* x);

    public:
        // Checks whether the diagram is consistent
        // (meaning that there are no vacuum bubbles)
        bool CheckConsistency() const;

        // Exports the diagram in the graphviz (dot) format
        QString ExportToDot(const QString&) const;
    
    private:
        QSet<TEdge*> Edges;
        QSet<TVertex*> Interactions;
        QSet<TVertex*> Correlations;
};
