#include "wick_edge.h"
#include "wick_task.h"
#include "wick_slot.h"

QString TWickTask::ToString() const
{
    QString result;
    QTextStream out(&result);
    
    out << "Wick task\nTotal slots: " << CurrentEdges.size() << "\n";
    for (int i = 0; i < CurrentEdges.size(); i++)
    {
        out << "    [" << CurrentEdges[i].Source << "] - p" << CurrentEdges[i].ParticleType << "- [" <<  CurrentEdges[i].Target << "]\n";
    }
    out << "End of wick task\n";
    out.flush();
    return result;
}

#define MSG(x) QTextStream(stderr) << x << "\n"

void TWickTask::Solve(QVector<TDiagram*> *output, bool checkConsistency)
{
    int i = -1;
    
    for (int k = 0; k < Slots.size(); k++)
    {
        if (Slots[k].IsFinalized())
            continue;
        i = k;
        break;
    }
    
    if (i == -1)
    {
        TDiagram* d = new TDiagram();
        ToDiagram(d);
        if (!checkConsistency || d->CheckConsistency()) output->append(d);
        else delete d;
        return;
    }
    
    TParticle* p = Slots[i].GetPendingParticleType();

    for (int j = i; j < Slots.size(); j++)
    {
        if (!TWickSlot::AllowContraction(Slots[i], Slots[j], p))
            continue;

        bool bad = false;
        
        for (int k = 0; k < j; k++)
        {
            if (k != i && TWickSlot::EquivalentSlots(Slots[k], Slots[j])) {
                bad = true;
                break;
            }
        }

        if (bad) continue;
        
        TWickSlot::Contract(Slots[i], Slots[j], p);
        CurrentEdges.append(TWickEdge(i, j, p));
        Solve(output, checkConsistency);
        TWickSlot::BreakContraction(Slots[i], Slots[j], p);
        CurrentEdges.pop_back();
    }
}

void TWickTask::ToDiagram(TDiagram* d)
{
    QVector<TVertex*> slotVertex(Slots.size());
    
    for (int i = 0; i < this->Slots.size(); i++)
    {
        if (this->Slots[i].Correlation) slotVertex[i] = d->AddCorrelationVertex();
        else slotVertex[i] = d->AddInteractionVertex();
    }
    
    for (int i = 0; i < this->CurrentEdges.size(); i++)
    {
        d->AddEdge(slotVertex[this->CurrentEdges[i].Source], slotVertex[this->CurrentEdges[i].Target], this->CurrentEdges[i].ParticleType);
    }
}
