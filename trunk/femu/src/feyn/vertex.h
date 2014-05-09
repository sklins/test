#pragma once
#include "graph_types.h"

class TVertex
{
public:
    friend class TDiagram;

private:
    QSet<TEdge*> IncidentEdges;
};
