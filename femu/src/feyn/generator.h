#pragma once
#include <util/global.h>
#include "diagram.h"
#include "feyn_rules.h"
#include "limitations.h"

class IGenerator {
public:
    /*abstract*/ virtual void Generate(QVector<TDiagram*> *output) = 0;
};


class TGenerator: public IGenerator {
public:
    TGenerator(const TFeynRules* rules, const TLimitations* limitations, bool includeKinematics):
        IsomorphismCheck(false), Rules(rules), Limitations(limitations), IncludeKinematics(includeKinematics) {}

    /*override*/ void Generate(QVector<TDiagram*> *output);

public:
    // Fill it up
    QVector<TParticle*> ExternalParticles;
    bool IsomorphismCheck;

private:
    void Brute(QSet<TInteraction*>::ConstIterator);
    void Apply();

private:
    const TFeynRules* Rules;
    const TLimitations* Limitations;
    bool IncludeKinematics;

    QVector<TDiagram*> *Output;
    uint32_t Total;

    QHash<TInteraction*, uint32_t> MaximalCfg;
    QHash<TInteraction*, uint32_t> CurrentCfg;
};
