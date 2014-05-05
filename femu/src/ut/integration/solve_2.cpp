#include "solve_2.h"
#include <util/global.h>
#include <ut/tests.h>
#include <feyn/particle.h>
#include <feyn/interaction.h>
#include <feyn/diagram.h>
#include <feyn/generator.h>

const uint32_t N = 5;

void IntegrationTest_Solve2() {
    MESSAGE("Initializing electron and photon..");
    TParticle electron("electron", LS_NORMAL);
    TParticle photon("photon", LS_DOTTED); // Should be LS_WAVE

    MESSAGE("Initializing the QED interaction vertex..");
    TInteraction qedVertex("QED vertex", false);
    qedVertex.Participants << &electron << &electron << &photon;
    
    MESSAGE("Initializing Feynman rules for the QED theory..");
    TFeynRules qedTheory;
    qedTheory.Particles << &electron << &photon;
    qedTheory.Interactions << &qedVertex;

    MESSAGE("Initializing limitations for the diagrams..");
    TLimitations limitations;
    limitations.LoopsLimit = TOptional<uint32_t>(1); // only tree-level diagrams
    limitations.ConnectedComponentsLimit = TOptional<uint32_t>(1); // only connected diagrams
    limitations.TotalInteractionsLimit = TOptional<uint32_t>(); // not limited
    limitations.InteractionLimits[&qedVertex] = 7;

    MESSAGE("Initializing the generator..");
    TGenerator generator(&qedTheory, &limitations, false /* only dynamics */);
    generator.ExternalParticles << &electron << &electron << &electron << &electron;

    MESSAGE("Initializing the output container..");
    QVector<TDiagram*> res;
    
    MESSAGE("Generating..");
    generator.Generate(&res);

    MESSAGE("Generated (" << res.size() << " diagrams). Calling graphviz...");

    QDir junk("junk/");
    QStringList svgs = junk.entryList(QStringList() << "*.svg");

    for (QStringList::Iterator i = svgs.begin(); i != svgs.end(); i++)
        QFile::remove(junk.absoluteFilePath(*i));

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
