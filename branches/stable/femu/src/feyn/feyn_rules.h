#pragma once
#include <util/global.h>
#include "particle.h"
#include "interaction.h"
#include "limitations.h"

struct TFeynRules {
    // Fill it up
    QSet<TParticle*> Particles;
    QSet<TInteraction*> Interactions;
    QString Name;

    void ImportFromXml(const QString &xmlFileName);

    bool CheckLimitations(const TLimitations& limitations) const;
};
