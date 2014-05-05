#include "feyn_rules.h"

bool TFeynRules::CheckLimitations(const TLimitations& limitations) const {
    if (limitations.TotalInteractionsLimit.HasValue())
        return true;

    // TODO: fixed LoopsLimit also renders diagrams amount finite.
    // In this case we have to iterate through all (infinite) sets
    // of interactions until the diagrams appear to have more loops than allowed.

    for (QSet<TInteraction*>::ConstIterator i = Interactions.begin();
            i != Interactions.end(); i++)
        if (!limitations.InteractionLimits.contains(*i)) return false;

    return true;
}
