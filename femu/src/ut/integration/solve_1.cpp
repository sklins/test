#include <ut/tests.h>
#include <limits.h>
#include "solve_1.h"

const uint32_t N = 7;

void IntegrationTest_Solve1() {
    MESSAGE("Initializing the scalar boson particle..");
    TParticle scalarBoson("scalar boson", LS_NORMAL);

    MESSAGE("Initializing the f4 interaction vertex..");
    TInteraction f4Int; f4Int.Participants.insert(&scalarBoson, 4);
    
    MESSAGE("Initializing Feynman rules for the f4 theory..");
    TFeynRules f4Theory;
    f4Theory.Particles << &scalarBoson;
    f4Theory.Interactions << &f4Int;

    MESSAGE("Initializing limitations for the diagrams..");
    TLimitations limitations(UINT_MAX, 0, UINT_MAX);
    limitations.InteractionLimits.insert(&f4Int, N); // limiting up to N f4 vertexes

    MESSAGE("Initializing the correlation task..");
    TCorrelation corr(&f4Theory, &limitations, true);
    corr.IncludeKinematics = false;
    corr.ExternalParticles << &scalarBoson << &scalarBoson;

    MESSAGE("Initializing the output container..");
    QVector<TDiagram*> res;
    
    MESSAGE("Solving..");
    corr.Solve(&res);

    MESSAGE("Solved (" << res.size() << " diagrams). Calling graphviz...");

    for (int i = 0; i < res.size(); i++) {
        QFile file("junk/d" + QString::number(i + 1) + ".svg");
        if (!file.open(QIODevice::WriteOnly)) {
            MESSAGE("Bad environment!");
            return;
        }
        file.close();

        res[i]->GenerateImage("Diagram_" + QString::number(i + 1), file.fileName());
        MESSAGE("Diagram_" << QString::number(i + 1) << ": " <<
                res[i]->CountConnectedComponents() << " connected components; " <<
                res[i]->CountLoops() << " loops");
    }

    MESSAGE("Done");
}
