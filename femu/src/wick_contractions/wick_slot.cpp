#include "wick_slot.h"

TWickSlot::TWickSlot(uint32_t particleTypeCount, uint32_t equivalenceClass, uint32_t inconsistencyMask)
    : EquivalenceClass(equivalenceClass), InconsistencyMask(inconsistencyMask)
{
    InitialFreedomDegrees.resize(particleTypeCount);
    CurrentFreedomDegrees.resize(particleTypeCount);
}

	
bool TWickSlot::EquivalentSlots(const TWickSlot &a, const TWickSlot &b)
{
    return a.EquivalenceClass == b.EquivalenceClass && a.CurrentFreedomDegrees == b.CurrentFreedomDegrees;
}

bool TWickSlot::AllowConnection(const TWickSlot &a, const TWickSlot &b, uint32_t particleType)
{
    ASSERT(particleType >= 0 && particleType < a.CurrentFreedomDegrees.size() && particleType < b.CurrentFreedomDegrees.size());
    return a.CurrentFreedomDegrees[particleType] > 0 && b.CurrentFreedomDegrees[particleType] > 0 && (a.InconsistencyMask & b.InconsistencyMask) != 0;
}
