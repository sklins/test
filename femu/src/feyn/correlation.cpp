#include "correlation.h"
#include "limitations.h"
#include <wick/wick_task.h>

void TCorrelation::Solve(QVector<TDiagram*> *output)
{
    QHash<TInteraction*, uint32_t> curLimits;
    bool last = false;
    uint32_t sumOfLimits = 0;
    
    for (QSet<TInteraction*>::Iterator i = FeynRules->Interactions.begin(); i != FeynRules->Interactions.end(); i++)
    {
        curLimits[*i] = 0;
    }
    if (!IncludeKinematics)
    {
        curLimits[(curLimits.end() - 1).key()] = 1;
        sumOfLimits++;
    }
    
    while (!last)
    {
        //точно есть баги
        
        last = true;
        for (QSet<TInteraction*>::Iterator i = FeynRules->Interactions.begin(); i != FeynRules->Interactions.end(); i++)
        {
            if (curLimits[*i] < this->Limitations->InteractionLimits[*i])
                last = false;
        }
        
        QHash<TInteraction*, uint32_t>::Iterator it = curLimits.end() - 1;
        
        if (sumOfLimits >= this->Limitations->TotalInteractionLimit)
        {
            sumOfLimits -= it.value();
            it.value() = 0;
            it--;
        }
        it.value()++;
        sumOfLimits++;
        
        while (it.value() == this->Limitations->InteractionLimits[it.key()])
        {
            sumOfLimits += it.value();
            it.value() = 0;
            it--;
            it.value()++;
            sumOfLimits++;
        }
        
        //ready set
        
        TWickTask* wickTask = new TWickTask();
        
        for (QHash<TInteraction*, uint32_t>::Iterator i = curLimits.begin(); i != curLimits.end(); i++)
        {
            for (uint32_t j = 0; j < i.value(); j++)
            {
                
                wickTask->Slots.resize(wickTask->Slots.size() + 1);
                
                //почему &? не ебу, просто так компилится
                //???????????????????????????????????????????????????????????????????
                
                i.key()->ExportToSlot(&wickTask->Slots[wickTask->Slots.size()-1]);
            }
        }
        
        wickTask->Solve(output);
    }
}
