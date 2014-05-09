#include "interaction.h"

void TInteraction::GenerateExampleDiagram(TDiagram *d) const {
    TVertex *in = d->AddInteractionVertex();
    for (QVector<TParticle*>::ConstIterator i = Participants.constBegin();
         i != Participants.constEnd(); i++) {
        TVertex *c = d->AddCorrelationVertex();
        d->AddEdge(in, c, *i);
    }
}
