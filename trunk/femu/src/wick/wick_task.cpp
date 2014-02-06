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
    
    out << "Wick task\nTotal slots: "<< CurrentEdges.size();
    for (int i = 0; i < CurrentEdges.size(); i++)
    {
        ASSERT(slotIndex.contains(CurrentEdges[i].Source) && slotIndex.contains(CurrentEdges[i].Target));
        out << "[" << slotIndex[CurrentEdges[i].Source] << "] - p" << CurrentEdges[i].ParticleType << "- [" << slotIndex[CurrentEdges[i].Target] << "]\n";
    }
    out.flush();
    return result;
}
