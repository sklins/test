#pragma once
#include <util/global.h>
#include "task.h"
#include "diagram.h"
#include "feynrules.h"

class TCorrelation : public ITask
{   
public:
    TCorrelation(TFeynRules* feynRules, TLimitations* limitations) : FeynRules(feynRules), Limitations(limitations) {}
public:
    TFeynRules* FeynRules;
    TLimitations* Limitations;
    bool IncludeKinematics;
    virtual void Solve(QVector<TDiagram*> *output);
};
