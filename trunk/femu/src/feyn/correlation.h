#pragma once
#include <util/global.h>
#include "task.h"
#include "diagram.h"
#include "feynrules.h"
#include <wick/wick_task.h>

class TCorrelation : public ITask
{   
public:
    TCorrelation(TFeynRules* feynRules, TLimitations* limitations, bool allowSimpleLoops) : FeynRules(feynRules), Limitations(limitations), AllowSimpleLoops(allowSimpleLoops) {}
public:
    TFeynRules* FeynRules;
    TLimitations* Limitations;
    QSet<TParticle*> ExternalParticles;
    bool IncludeKinematics;
    QHash<TInteraction*, uint32_t> CurLimits;
    bool AllowSimpleLoops;
    
    void SetToZero(uint32_t &totalSum);
    bool LastCombination();
    bool NormalTotalSum(uint32_t &totalSum);
    void NextCombination(uint32_t &totalSum);
    void ToWickTask(TWickTask* wickTask);
    virtual void Solve(QVector<TDiagram*> *output);
};
