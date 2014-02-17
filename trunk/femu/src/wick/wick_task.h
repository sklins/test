#pragma once
#include <util/global.h>
#include "wick_slot.h"
#include "wick_edge.h"

class TWickTask
{    
    public:
        QVector<TWickSlot> Slots;
        QString ToString() const;
        void Solve();
   
    private:
        QVector<TWickEdge> CurrentEdges;
};

