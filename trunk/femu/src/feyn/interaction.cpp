#include "interaction.h"

void TInteraction::ExportToSlot(TWickSlot* res)
{
    for (QHash<TParticle*, uint32_t>::Iterator i = (this->Participants).begin(); i != (this->Participants).end(); i++)
    {
        res->InitializeFreedomDegree(i.key(), i.value());
    }
}
