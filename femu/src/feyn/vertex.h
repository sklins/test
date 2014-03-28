#pragma once

class TVertex
{
public:
    friend class TDiagram;
private:
    QSet<TEdge*> IncidentEdges;
};
