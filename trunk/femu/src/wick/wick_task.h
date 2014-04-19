#pragma once
#include <util/global.h>
#include "wick_slot.h"
#include "wick_edge.h"
#include <feyn/diagram.h>

class TWickTask
{    
    public:
        QVector<TWickSlot> Slots;
        QString ToString() const;
        void Solve();
        void ToDiagram(TDiagram* d);
   
    private:
        QVector<TWickEdge> CurrentEdges;
};

