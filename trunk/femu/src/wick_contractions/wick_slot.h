#pragma once
#include <util/global.h>

class TWickSlot
{    
    public:
        TWickSlot(uint32_t particleTypeCount, uint32_t equivalenceClass, uint32_t inconsistencyMask);
    
    private:
        QVector<uint32_t> InitialFreedomDegrees;
        QVector<uint32_t> CurrentFreedomDegrees;
        uint32_t EquivalenceClass;
        uint32_t InconsistencyMask;
};

