#pragma once
#include <util/global.h>
#include "edge.h"
#include "vertex.h"
#include "particle.h"

class TDiagram
{
    friend class TSimplifiedDiagram;
    friend bool CheckIsomorphism(const TDiagram &a, const TDiagram &b);

    public:
        ~TDiagram ();
    public:
        TVertex* AddInteractionVertex();
        TVertex* AddCorrelationVertex();
        TEdge* AddEdge(TVertex* a, TVertex* b,TParticle* p);
        void RemoveEdge(TEdge* e);
        void RemoveVertex(TVertex* x);

    public:
        // Checks whether the diagram is consistent
        // (meaning that there are no vacuum bubbles)
        bool CheckConsistency() const;

        // Exports the diagram in the graphviz (dot) format
        QString ExportToDot(const QString&) const;
        QByteArray GenerateImageData(const QString &diagramName = "") const;
        void GenerateImage(const QString& diagramName, const QString& fileName) const;
        uint32_t CountConnectedComponents() const;
        uint32_t CountLoops() const;

    private:
        QSet<TEdge*> Edges;
        QSet<TVertex*> Interactions;
        QSet<TVertex*> Correlations;
};
