#include "wick_edge.h"
#include "wick_task.h"
#include "wick_slot.h"

QString TWickTask::ToString() const
{
    QHash<const TWickSlot*, int> slotIndex;
    
    for (int i = 0; i < Slots.size(); i++)
    {
        slotIndex[&Slots[i]] = i;
    }
    
    QString result;
    QTextStream out(&result);
    
    out << "Wick task\nTotal slots: " << CurrentEdges.size() << "\n";
    for (int i = 0; i < CurrentEdges.size(); i++)
    {
        ASSERT(slotIndex.contains(CurrentEdges[i].Source) && slotIndex.contains(CurrentEdges[i].Target));
        out << "    [" << slotIndex[CurrentEdges[i].Source] << "] - p" << CurrentEdges[i].ParticleType << "- [" <<  slotIndex[CurrentEdges[i].Target] << "]\n";
    }
    out << "End of wick task\n";
    out.flush();
    return result;
}

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
    
    uint32_t p = Slots[i].GetPendingParticleType();
    
    for (int j = i; j < Slots.size(); j++)
    {
        if (!TWickSlot::AllowContraction(Slots[i], Slots[j], p))
            continue;
        
        for (int k = i + 1; k < j; k++)
        {
            if (TWickSlot::EquivalentSlots(Slots[k], Slots[j]))
                continue;
        }
        
        TWickSlot::Contract(Slots[i], Slots[j], p);
        CurrentEdges.append(TWickEdge(&Slots[i], &Slots[j], p));
        Solve(output, checkConsistency);
        TWickSlot::BreakContraction(Slots[i], Slots[j], p);
        CurrentEdges.pop_back();
    }
}

void TWickTask::ToDiagram(TDiagram* d)
{
    QHash<const TWickSlot*, TVertex*> slotVertex;
    
    for (int i = 0; i < this->Slots.size(); i++)
    {
        if (this->Slots[i].Correlation) slotVertex[&Slots[i]] = d->AddCorrelationVertex();
        else slotVertex[&Slots[i]] = d->AddInteractionVertex();
    }
    
    for (int i = 0; i < this->CurrentEdges.size(); i++)
    {
        d->AddEdge(slotVertex[this->CurrentEdges[i].Source], slotVertex[this->CurrentEdges[i].Target], this->ParticleBase[i]);
    }
}
