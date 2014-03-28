#include "diagram.h"

TDiagram::~TDiagram()
{
    for (QSet<TInternalEdge*>::Iterator i = InternalEdges.begin();
         i != InternalEdges.end(); i++)
    {
        delete *i;
    }
    for (QSet<TExternalEdge*>::Iterator i = ExternalEdges.begin();
         i != ExternalEdges.end(); i++)
    {
        delete *i;
    }
    for (QSet<TInteractionVertex*>::Iterator i = InteractionVertexes.begin();
         i != InteractionVertexes.end(); i++)
    {
        delete *i;
    }
}
