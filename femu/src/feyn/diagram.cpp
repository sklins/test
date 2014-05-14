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

TEdge* TDiagram::AddEdge(TVertex* a, TVertex* b, TParticle *p)
{
    TEdge *ab = new TEdge(a, b, p);
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
    QSet<TVertex*> visited;
    QStack <TVertex*> s;
    TVertex* a;
    
    for (QSet<TVertex*>::ConstIterator cor = Correlations.begin(); cor != Correlations.end(); cor++)
    {
        ASSERT((*cor)->IncidentEdges.size() == 1);
        visited << *cor;
        s.push(*cor);
    }
    
    while (!s.empty())
    {
        a = s.top();
        s.pop();
        for (QSet<TEdge*>::ConstIterator i = a->IncidentEdges.begin(); i != a->IncidentEdges.end(); i++)
        {
            ASSERT (((*i)->A == a) || ((*i)->B == a));
            TVertex* b = ((*i)->A != a) ? (*i)->A : (*i)->B;
            if (!visited.contains(b))
            {
                s.push(b);
                visited << b;
            }
        }
    }

    for (QSet<TVertex*>::ConstIterator i = Interactions.begin(); i != Interactions.end(); i++)
        if (!visited.contains(*i)) return false;
    return true;
}

QString TDiagram::ExportToDot(const QString& graphName) const {
    QString result;
    QTextStream out(&result);
    QHash<TVertex*, uint32_t> vertexNames;
    uint32_t num = 0;
    double levelsgap = 0.9;
    double nodesep = 0.3;

    out << "graph {\n    mode=ipsep\n    diredgeconstraints=true\n    levelsgap=" << levelsgap << "\n    nodesep=" << nodesep << "\n    overlap=ipsep\n\n";
    out << "    layout = neato;\n";
    out << "    labelloc=\"t\";\n";
    out << "    label=\"" << graphName << "\";\n\n";
    
    //А ПОЧЕМУ ОБЪЯВЛЕН ХЭШ А В ЦИКЛЕ СЕТ?????????????????????????????????????????????????
    
    for (QSet<TVertex*>::ConstIterator i = Correlations.begin(); i != Correlations.end(); i++)
    {
        vertexNames[*i] = num++;
        out << "    v" << vertexNames[*i] << " [shape=none,label=\"\"];\n";
    }
    
    for (QSet<TVertex*>::ConstIterator i = Interactions.begin(); i != Interactions.end(); i++)
    {
        vertexNames[*i] = num++;
        out << "    v" << vertexNames[*i] << " [shape=point,label=\"\"];\n";
    }
    out << "\n";
    
    for (QSet<TEdge*>::ConstIterator i = Edges.begin(); i != Edges.end(); i++)
    {
        out << "    v" << vertexNames[(*i)->A] << " -- v" <<  vertexNames[(*i)->B];
        switch ((*i)->Particle->GetLineShape())
        {
            case LS_DASHED:
                out << " [style=dashed]";
                break;
                
            case LS_DOTTED:
                out << " [style=dotted]";
                break;
                
            default:
                break;
        }
        out << ";\n";
    }
    out << "}\n";
    
    out.flush();
    return result;
}

QByteArray TDiagram::GenerateImageData(const QString& diagramName) const
{
    QProcess graphviz;
    graphviz.start("neato", QStringList() << "-Tsvg");
    graphviz.waitForStarted();
    QTextStream graphvizInput(&graphviz);
    graphvizInput << ExportToDot(diagramName);
    graphvizInput.flush();
    graphviz.closeWriteChannel();

    graphviz.waitForFinished();

    QByteArray result = graphviz.readAll();
    return result;
}

void TDiagram::GenerateImage(const QString &diagramName, const QString &fileName) const {
    QByteArray data = GenerateImageData(diagramName);
    QFile output(fileName);
    output.open(QIODevice::WriteOnly);
    output.write(data);
    output.close();
}

uint32_t TDiagram::CountConnectedComponents() const
{
    QSet<TVertex*> visited;
    QStack <TVertex*> s;
    TVertex* a;
    uint32_t kol = 0;
    for (QSet<TVertex*>::ConstIterator cor = Correlations.begin(); cor != Correlations.end(); cor++)
    {
        ASSERT((*cor)->IncidentEdges.size() == 1);
        if (!visited.contains(*cor))
        {
            kol++;
            visited << *cor;
            s.push(*cor);
            while (!s.empty())
            {
                a = s.top();
                s.pop();
                for (QSet<TEdge*>::ConstIterator i = a->IncidentEdges.begin(); i != a->IncidentEdges.end(); i++)
                {
                    ASSERT (((*i)->A == a) || ((*i)->B == a));
                    TVertex* b = ((*i)->A != a) ? (*i)->A : (*i)->B;
                    if (!visited.contains(b))
                    {
                        s.push(b);
                        visited << b;
                    }
                }
            }
        }
    }
    return kol;
}

uint32_t TDiagram::CountLoops() const
{
    return (CountConnectedComponents() + this->Edges.size() - this->Interactions.size() - this->Correlations.size());
}


