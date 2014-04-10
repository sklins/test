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

TVertex* TDiagram::AddInteractionVertex()
{
    TVertex *v = new TVertex();
    Interactions << v;
    return v;
}

TVertex* TDiagram::AddCorrelationVertex()
{
    TVertex *v = new TVertex();
    Correlations << v;
    return v;
}

TEdge* TDiagram::AddEdge(TVertex* a, TVertex* b)
{
    TEdge *ab = new TEdge(a, b);
    Edges << ab;
    a->IncidentEdges << ab;
    b->IncidentEdges << ab;
    return ab;
}

void TDiagram::RemoveEdge(TEdge* e)
{
    ASSERT(e->A != NULL && e->A->IncidentEdges.contains(e));
    e->A->IncidentEdges.remove(e);
    ASSERT(e->B != NULL && e->B->IncidentEdges.contains(e));
    e->B->IncidentEdges.remove(e);
    Edges.remove(e);
    delete e;
}

void TDiagram::RemoveVertex(TVertex* x)
{
    while (x->IncidentEdges.size() > 0)
        RemoveEdge(*x->IncidentEdges.begin());
    ASSERT(Interactions.contains(x) ^ Correlations.contains(x));
    if (Interactions.contains(x)) Interactions.remove(x);
    else Correlations.remove(x);
    delete x;
}

bool TDiagram::CheckConsistency() const {
    NOT_IMPLEMENTED;
}

QString TDiagram::ExportToDot(const QString& graphName) const {
    QString result;
    QTextStream out(&result);
    
    out << "graph " << graphName << " {\n";
    for (QSet<TVertex*>::ConstIterator i = Correlations.begin(); i != Correlations.end(); i++)
        out << "    " << *i << " [shape=none label=""];\n";
    
    for (QSet<TVertex*>::ConstIterator i = Interactions.begin(); i != Interactions.end(); i++)
        out << "    " << *i << " [shape=point label=""];\n";
    out << "\n";
    
    for (QSet<TEdge*>::ConstIterator i = Edges.begin(); i != Edges.end(); i++)
    {
        out << "    " << (*i)->A << " -- " << (*i)->B << ";\n";
    }
    out << "}\n";
    
    out.flush();
    return result;
}
