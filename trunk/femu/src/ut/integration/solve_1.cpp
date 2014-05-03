#include <ut/tests.h>
#include "solve_1.h"

void IntegrationTest_Solve1() {
    // Scalar boson particle
    TParticle scalarBoson("scalar boson", LS_NORMAL);

    // F4 interaction vertex
    TInteraction f4Int; f4Int.Participants.insert(&scalarBoson, 4);
    
    // Feynman rules for F4 theory
    TFeynRules f4Theory;
    f4Theory.Particles << &scalarBoson;
    f4Theory.Interactions << &f4Int;

    // Limitations
    TLimitations limitations(0, 1, 0); // connected diagrams without loop limitations
    // Or 0 means tree-level limitations?
    limitations.InteractionLimits.insert(&f4Int, 2); // limiting up to two f4 vertexes

    TCorrelation corr(&f4Theory, &limitations);

    QVector<TDiagram*> res;
    
    corr.Solve(&res); // Where are my external particles?
}
