#include "solve_2.h"
#include <util/global.h>
#include <ut/tests.h>
#include <feyn/particle.h>
#include <feyn/interaction.h>
#include <feyn/diagram.h>
#include <feyn/generator.h>

const uint32_t N = 5;

// Non-Abelian gauge theory (Yang-Mills model)

void IntegrationTest_Solve3() {
    MESSAGE("Initializing N/A gauge particles..");
    TParticle fermion("fermion", LS_NORMAL);
    TParticle boson("gauge boson", LS_DASHED); // Should be LS_WAVE
    TParticle ghost("Faddev-Popov ghost", LS_DOTTED); // Gauge fixing particle

    MESSAGE("Initializing the N/A gauge 2-fermion + boson interaction vertex..");
    TInteraction ffbVertex("2F + B vertex", false);
    ffbVertex.Participants << &fermion << &fermion << &boson;

    MESSAGE("Initializing the N/A gauge 3-boson interaction vertex..");
    TInteraction bbbVertex("3B vertex", false);
    bbbVertex.Participants << &boson << &boson << &boson;

    MESSAGE("Initializing the N/A gauge 4-boson interaction vertex..");
    TInteraction bbbbVertex("4B vertex", false);
    bbbbVertex.Participants << &boson << &boson << &boson << &boson;

    MESSAGE("Initializing the N/A gauge ghost interaction vertex..");
    TInteraction ggbVertex("2g + B ghost vertex", false);
    ggbVertex.Participants << &boson << &ghost << &ghost;

    MESSAGE("Initializing Feynman rules for the N/A gauge theory..");
    TFeynRules NAGaugeTheory;
    NAGaugeTheory.Particles << &fermion << &boson << &ghost;
    NAGaugeTheory.Interactions << &ffbVertex << &bbbVertex << &bbbbVertex << &ggbVertex;


    MESSAGE("Initializing limitations for the diagrams..");
    TLimitations limitations;
    limitations.LoopsLimit = TOptional<uint32_t>(1);
    limitations.ConnectedComponentsLimit = TOptional<uint32_t>(1);
    limitations.TotalInteractionsLimit = TOptional<uint32_t>(N);

    MESSAGE("Initializing the generator..");
    TGenerator generator(&NAGaugeTheory, &limitations, false /* only dynamics */);
    generator.ExternalParticles << &fermion << &fermion << &fermion << &fermion;
    generator.IsomorphismCheck = true;

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

    MESSAGE("Done (N/A gauge theory; fermion scattering; max. 5 ints; only connected; max. 1 loop) : should be 8 diagrams");

    if (res.size() == 8)
        MESSAGE("OK");
    else MESSAGE("ERROR! " << res.size() << " diagrams generated instead of 8!");
}
