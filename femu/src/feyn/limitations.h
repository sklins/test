#pragma once
#include <util/global.h>

class TLimitations
{
public:
    TLimitations(uint32_t loopsLimit, uint32_t connectedComponentsLimit, uint32_t totalInteractionLimit) : LoopsLimit(loopsLimit), ConnectedComponentsLimit(connectedComponentsLimit), TotalInteractionLimit(totalInteractionLimit);
public:
    uint32_t LoopsLimit;
    uint32_t ConnectedComponentsLimit;
    QHash<TInteraction*, uint32_t> InteractionLimits;
    uint32_t TotalInteractionLimit;
};
