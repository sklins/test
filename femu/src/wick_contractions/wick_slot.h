#pragma once
#include <util/global.h>

class TWickSlot
{    
    public:
        TWickSlot(uint32_t particleTypeCount, uint32_t equivalenceClass, uint32_t inconsistencyMask);
        
    public:
        static bool EquivalentSlots(const TWickSlot &a, const TWickSlot &b);
        static bool AllowConnection(const TWickSlot &a, const TWickSlot &b, uint32_t particleType);
        static void Contract(TWickSlot &a, TWickSlot &b, uint32_t particleType);
        static void BreakContraction(TWickSlot &a, TWickSlot &b, uint32_t particleType);
    
    private:
        QVector<uint32_t> InitialFreedomDegrees;
        QVector<uint32_t> CurrentFreedomDegrees;
        uint32_t EquivalenceClass;
        uint32_t InconsistencyMask;
};

