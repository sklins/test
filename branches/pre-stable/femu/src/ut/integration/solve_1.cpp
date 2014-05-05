#include <util/global.h>
#include <ut/tests.h>
#include <feyn/particle.h>
#include <feyn/interaction.h>
#include <feyn/diagram.h>
#include <feyn/generator.h>

const uint32_t N = 3;

void IntegrationTest_Solve1() {
    MESSAGE("Initializing the scalar boson particle..");
    TParticle scalarBoson("scalar boson", LS_NORMAL);

    MESSAGE("Initializing the f4 interaction vertex..");
    TInteraction f4Int("f4 interaction vertex", true);
    f4Int.Participants << &scalarBoson << &scalarBoson << &scalarBoson << &scalarBoson;
    
    MESSAGE("Initializing Feynman rules for the f4 theory..");
    TFeynRules f4Theory;
    f4Theory.Particles << &scalarBoson;
    f4Theory.Interactions << &f4Int;

    MESSAGE("Initializing limitations for the diagrams..");
    TLimitations limitations;
    limitations.LoopsLimit = TOptional<uint32_t>(); // not limited
    limitations.ConnectedComponentsLimit = TOptional<uint32_t>(); // not limited
    limitations.TotalInteractionsLimit = TOptional<uint32_t>(); // not limited
    limitations.InteractionLimits[&f4Int] = 3;

    MESSAGE("Initializing the generator..");
    TGenerator generator(&f4Theory, &limitations, false /* only dynamics */);
    generator.ExternalParticles << &scalarBoson << &scalarBoson;

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
