#pragma once
#include <util/global.h>
#include <wick/wick_slot.h>

class TInteraction
{   
public:
    void ExportToSlot(TWickSlot* res, bool AllowSimpleLoops);
    QHash<TParticle*, uint32_t> Participants;
};
