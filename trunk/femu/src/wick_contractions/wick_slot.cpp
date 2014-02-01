#include "wick_slot.h"

TWickSlot::TWickSlot(uint32_t particleTypeCount, uint32_t equivalenceClass, uint32_t inconsistencyMask)
    : EquivalenceClass(equivalenceClass), InconsistencyMask(inconsistencyMask)
{
    InitialFreedomDegrees.resize(particleTypeCount);
    CurrentFreedomDegrees.resize(particleTypeCount);
}

