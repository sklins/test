#include "wick_slot.h"

TWickSlot::TWickSlot(uint32_t particleTypeCount, uint32_t equivalenceClass, uint32_t inconsistencyMask, bool allowSimpleLoops)
    : EquivalenceClass(equivalenceClass), InconsistencyMask(inconsistencyMask), AllowSimpleLoops(allowSimpleLoops)
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
    ASSERT(particleType < (uint32_t)a.CurrentFreedomDegrees.size() && particleType < (uint32_t)b.CurrentFreedomDegrees.size());
    if (&a == &b)
    {
        return a.CurrentFreedomDegrees[particleType] > 1 && a.AllowSimpleLoops;
    }
    else
    {
        return a.CurrentFreedomDegrees[particleType] > 0 && b.CurrentFreedomDegrees[particleType] > 0 && (a.InconsistencyMask & b.InconsistencyMask) != 0;
    }
}

void TWickSlot::Contract(TWickSlot &a, TWickSlot &b, uint32_t particleType)
{
    if (&a == &b)
    {
        ASSERT(a.CurrentFreedomDegrees[particleType] > 1);
        a.CurrentFreedomDegrees[particleType] -= 2;
    }
    else
    {
        ASSERT(a.CurrentFreedomDegrees[particleType] > 0 && b.CurrentFreedomDegrees[particleType] > 0);
        a.CurrentFreedomDegrees[particleType]--;
        b.CurrentFreedomDegrees[particleType]--;
    }
}

void TWickSlot::BreakContraction(TWickSlot &a, TWickSlot &b, uint32_t particleType)
{
    ASSERT(a.CurrentFreedomDegrees[particleType] < a.InitialFreedomDegrees[particleType]
        && b.CurrentFreedomDegrees[particleType] < b.InitialFreedomDegrees[particleType]);
    a.CurrentFreedomDegrees[particleType]++;
    b.CurrentFreedomDegrees[particleType]++; 
}

void TWickSlot::InitializeFreedomDegree(uint32_t particleType, uint32_t count)
{
    ASSERT((uint32_t)CurrentFreedomDegrees.size() > particleType && InitialFreedomDegrees[particleType] == 0 && CurrentFreedomDegrees[particleType] == 0);
    CurrentFreedomDegrees[particleType] = count;
    InitialFreedomDegrees[particleType] = count;
}
