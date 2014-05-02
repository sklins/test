#include "correlation.h"

void TCorrelation::Solve(QVector<TDiagram*> *output)
{
    QHash<TInteraction*, uint32_t> InteractionNumbers;
    for (QSet<TInteraction*>::Iterator i = (FeynRules->Interactions).begin(); i != (FeynRules->Interactions).end(); i++)
    {
        //for (uint32_t lim = 0; lim < InteractionLimits[*i]; lim++)
        {
            
        }
    }
}
