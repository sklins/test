#pragma once
#include <util/global.h>
#include <util/optional.h>
#include "interaction.h"

typedef TOptional<uint32_t> TOptionalLimit;

struct TLimitations {
    // Fill these up
    TOptionalLimit LoopsLimit;
    TOptionalLimit ConnectedComponentsLimit;
    TOptionalLimit TotalInteractionsLimit;
    QHash<const TInteraction*, uint32_t> InteractionLimits;
};
