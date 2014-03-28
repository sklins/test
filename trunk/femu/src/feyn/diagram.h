#pragma once
#include <util/global.h>
#include "internal_edge.h"
#include "external_edge.h"
#include "interaction_vertex.h"

class TDiagram
{
    public:
        ~TDiagram ();
    
    private:
        QSet<TInternalEdge*> InternalEdges;
        QSet<TExternalEdge*> ExternalEdges;
        QSet<TInteractionVertex*> InteractionVertexes;
};
