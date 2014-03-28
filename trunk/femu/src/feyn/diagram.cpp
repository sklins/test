#include "diagram.h"

TDiagram::~TDiagram()
{
    for (QSet<TEdge*>::Iterator i = Edges.begin(); i != Edges.end(); i++)
        delete *i;

    for (QSet<TVertex*>::Iterator i = Interactions.begin(); i != Interactions.end(); i++)
        delete *i;

    for (QSet<TVertex*>::Iterator i = Correlations.begin(); i != Correlations.end(); i++)
        delete *i;
}
