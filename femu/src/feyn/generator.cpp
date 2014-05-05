#include "generator.h"
#include <wick/wick_task.h>


void TGenerator::Brute(QSet<TInteraction*>::ConstIterator it) {
    if (it == Rules->Interactions.end()) { // Applying CurrentCfg
        Apply();
        return;
    }

    uint32_t limit = MaximalCfg[*it];
    if (Limitations->TotalInteractionsLimit.HasValue() && Total + limit > Limitations->TotalInteractionsLimit.Get())
        limit = Limitations->TotalInteractionsLimit.Get() - Total;

    for (uint32_t i = 0; i <= limit; i++) {
        CurrentCfg[*it] = i;
        Total += i;
        Brute(it + 1);
        Total -= i;
    }
}

void TGenerator::Apply() {
    if (Total == 0 && !IncludeKinematics)
        return;

    TWickTask wickTask;

    // Adding correlation slots
    for (QVector<TParticle*>::ConstIterator i = ExternalParticles.begin();
         i != ExternalParticles.end(); i++) {
        TWickSlot slot(0, 0, false, true);
        QHash<TParticle*, uint32_t> freedomDegrees;

        // Setting all freedom degrees to zero
        for (QSet<TParticle*>::ConstIterator p = Rules->Particles.begin();
             p != Rules->Particles.end(); p++) {
            freedomDegrees.insert(*p, 0);
        }

        // Adding the correlator particle
        freedomDegrees[*i] = 1;

        // Initializing slot freedom degrees
        for (QHash<TParticle*, uint32_t>::ConstIterator k = freedomDegrees.begin();
             k != freedomDegrees.end(); k++) {
            slot.InitializeFreedomDegree(k.key(), k.value());
        }

    // Adding the correlator slot
        wickTask.Slots << slot;
    }

    // Adding interaction slots
    for (QSet<TInteraction*>::ConstIterator i = Rules->Interactions.begin();
         i != Rules->Interactions.end(); i++) {
        for (uint32_t j = 0; j < CurrentCfg[*i]; j++) { // we have some copies of the same interaction
            TWickSlot slot(0, 0, (*i)->AllowSimpleLoops, false);
            QHash<TParticle*, uint32_t> freedomDegrees;

            // Setting all freedom degrees to zero
            for (QSet<TParticle*>::ConstIterator p = Rules->Particles.begin();
                 p != Rules->Particles.end(); p++) {
                freedomDegrees.insert(*p, 0);
            }

            // Adding participant particles
            for (QVector<TParticle*>::ConstIterator p = (*i)->Participants.constBegin();
                 p != (*i)->Participants.constEnd(); p++) {
                freedomDegrees[*p]++;
            }

            // Initializing slot freedom degrees
            for (QHash<TParticle*, uint32_t>::ConstIterator k = freedomDegrees.begin();
                 k != freedomDegrees.end(); k++) {
                slot.InitializeFreedomDegree(k.key(), k.value());
            }

            // Adding the slot
            wickTask.Slots << slot;
        }
    }

    // Writing the info
    QTextStream log(stderr);
    log << "TGenerator::Generate: ";

    for (QSet<TInteraction*>::ConstIterator i = Rules->Interactions.begin();
         i != Rules->Interactions.end(); i++) {
        log << (*i)->Name << " (" << CurrentCfg[*i] << "), ";
    }

    log << "solving..\n";

    QVector<TDiagram*> pre;
    wickTask.Solve(&pre, ExternalParticles.size() > 0); // We generate either bubbles or diagrams without bubbles

    for (QVector<TDiagram*>::Iterator i = pre.begin(); i != pre.end(); i++) {
        if (Limitations->ConnectedComponentsLimit.HasValue()) {
            uint32_t components = (*i)->CountConnectedComponents();
            if (components > Limitations->ConnectedComponentsLimit.Get())
                continue;
        }

        if (Limitations->LoopsLimit.HasValue()) {
            uint32_t loops = (*i)->CountLoops();
            if (loops > Limitations->LoopsLimit.Get())
                continue;
        }

        Output->push_back(*i);
    }
}

void TGenerator::Generate(QVector<TDiagram *> *output) {
    if (!Rules->CheckLimitations(*Limitations))
        throw "Limitations do not render diagrams finite!";

    for (QSet<TInteraction*>::ConstIterator i = Rules->Interactions.begin();
         i != Rules->Interactions.end(); i++) {
        if (Limitations->InteractionLimits.contains(*i))
            MaximalCfg.insert(*i, Limitations->InteractionLimits.value(*i));
        else MaximalCfg.insert(*i, Limitations->TotalInteractionsLimit.Get());

        // XXX: It is possible (not now, but still) that neither the total interactions limit
        // nor the limit for the current interaction type is set.
    }

    Output = output;
    Total = 0;

    Brute(Rules->Interactions.begin());
}
