#include "interaction.h"

void TInteraction::ExportToSlot(TWickSlot* res, bool allowSimpleLoops)
{
    for (QHash<TParticle*, uint32_t>::Iterator i = (this->Participants).begin(); i != (this->Participants).end(); i++)
    {
        res->InitializeFreedomDegree(i.key(), i.value());
        res->EquivalenceClass = 0;
        res->InconsistencyMask = 0;
        res->AllowSimpleLoops = allowSimpleLoops;
        //то есть вызывать только для интеракшанов
        res->Correlation = false;
    }
}
