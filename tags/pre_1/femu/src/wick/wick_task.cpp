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

void TWickTask::Solve()
{
    QTextStream output(stdout);
    
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
        output << ToString() << "\n";
        output.flush();
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
        Solve();
        TWickSlot::BreakContraction(Slots[i], Slots[j], p);
        CurrentEdges.pop_back();
    }
}
