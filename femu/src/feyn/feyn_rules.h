#pragma once
#include <util/global.h>
#include <QtXml>
#include "particle.h"
#include "interaction.h"
#include "limitations.h"

struct TFeynRules {
    // Fill it up
    QSet<TParticle*> Particles;
    QSet<TInteraction*> Interactions;
    QString Name;

    void ImportFromXmlElement(QDomElement e_document);

    bool CheckLimitations(const TLimitations& limitations) const;
};
