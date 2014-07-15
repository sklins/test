#pragma once
#include <util/global.h>
#include <wick/wick_slot.h>
#include "diagram.h"

struct TInteraction
{
    TInteraction(const QString& name, bool allowSimpleLoops = false):
        Name(name), AllowSimpleLoops(allowSimpleLoops) {}

    QString Name;
    bool AllowSimpleLoops;

    // Fill it up
    QVector<TParticle*> Participants;

    void GenerateExampleDiagram(TDiagram *d) const;
};
