#include "wick_slot.h"

TWickSlot::TWickSlot(uint32_t equivalenceClass, uint32_t inconsistencyMask, bool allowSimpleLoops, bool correlation)
    : EquivalenceClass(equivalenceClass), InconsistencyMask(inconsistencyMask), AllowSimpleLoops(allowSimpleLoops), Correlation(correlation)
{
}


TWickSlot::TWickSlot()
    : EquivalenceClass(), InconsistencyMask(), AllowSimpleLoops(), Correlation()
{
}

bool TWickSlot::EquivalentSlots(const TWickSlot &a, const TWickSlot &b)
{
    return a.EquivalenceClass == b.EquivalenceClass && a.CurrentFreedomDegrees == b.CurrentFreedomDegrees;
}

bool TWickSlot::AllowContraction(const TWickSlot &a, const TWickSlot &b, TParticle* particleType)
{
    ASSERT(a.CurrentFreedomDegrees.contains(particleType) && b.CurrentFreedomDegrees.contains(particleType));
    if (&a == &b)
    {
        return a.CurrentFreedomDegrees[particleType] > 1 && a.AllowSimpleLoops;
    }
    else
    {
        return a.CurrentFreedomDegrees[particleType] > 0 && b.CurrentFreedomDegrees[particleType] > 0 && (a.InconsistencyMask & b.InconsistencyMask) == 0;
    }
}

void TWickSlot::Contract(TWickSlot &a, TWickSlot &b, TParticle* particleType)
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

void TWickSlot::BreakContraction(TWickSlot &a, TWickSlot &b, TParticle* particleType)
{
    if (&a == &b)
    {
        ASSERT(a.CurrentFreedomDegrees[particleType] < a.InitialFreedomDegrees[particleType] - 1);
        a.CurrentFreedomDegrees[particleType] += 2;
    }
    else
    {
        ASSERT(a.CurrentFreedomDegrees[particleType] < a.InitialFreedomDegrees[particleType]
            && b.CurrentFreedomDegrees[particleType] < b.InitialFreedomDegrees[particleType]);
        a.CurrentFreedomDegrees[particleType]++;
        b.CurrentFreedomDegrees[particleType]++; 
    }
}

void TWickSlot::InitializeFreedomDegree(TParticle*  particleType, uint32_t count)
{
    ASSERT(!InitialFreedomDegrees.contains(particleType) && !CurrentFreedomDegrees.contains(particleType));
    CurrentFreedomDegrees.insert(particleType, count);
    InitialFreedomDegrees.insert(particleType, count);
}

bool TWickSlot::IsFinalized()  const
{
    for (QHash<TParticle*, uint32_t>::ConstIterator i = CurrentFreedomDegrees.begin(); i != CurrentFreedomDegrees.end(); ++i)
        if (i.value() > 0) return false;
    return true;    
}

TParticle* TWickSlot::GetPendingParticleType() const
{
    ASSERT(!IsFinalized());
    for (QHash<TParticle*, uint32_t>::ConstIterator i = CurrentFreedomDegrees.begin(); i != CurrentFreedomDegrees.end(); ++i)
        if (i.value() > 0) return i.key();
    return NULL;
}
