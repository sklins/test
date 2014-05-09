#include <QtCore>
#include <util/exception.h>
#include <ut/tests.h>
#include <ut/integration/wick_example.h>
#include <ut/integration/solve_1.h>
#include <ut/integration/solve_2.h>
#include <ut/integration/solve_3.h>

#include <feyn/diagram.h>
#include <feyn/feyn_rules.h>
void PreGui() {
    QDir examples("examples");
    QStringList entries = examples.entryList(QStringList() << "*.xml");
    int n = entries.size();
    QVector<TFeynRules> theories; theories.resize(n);

    QTextStream input(stdin), output(stdout);

    for (int i = 0; i < n; i++) {
        output << "Parsing " << entries[i] << "..\n";
        output.flush();
        theories[i].ImportFromXml(examples.absoluteFilePath(entries[i]));
        output << "Imported #" << i << " " << theories[i].Name << "\n";
        output.flush();
    }

    output << "Enter #"; output.flush();
    int k; input >> k;
    output << "Generating for " << theories[k].Name << "\n";

    for (QSet<TInteraction*>::ConstIterator i = theories[k].Interactions.constBegin();
         i != theories[k].Interactions.constEnd(); i++) {
        TInteraction *in = *i;
        TDiagram d;
        in->GenerateExampleDiagram(&d);
        d.GenerateImage("example", in->Name + ".svg");
    }

    output.flush();
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QStringList args = app.arguments();

    if (args.size() == 1 || args[1] == "ut") {
        // Run unit tests
        try {
            RunUnittests();
        } catch (const TException &e) {
            e.Display();
        }
    } else if (args[1] == "wick-example") {
        GenerateContractionsForSampleTask();
    } else if (args[1] == "solve-1") {
        IntegrationTest_Solve1();
    } else if (args[1] == "solve-2") {
        IntegrationTest_Solve2();
    } else if (args[1] == "solve-3") {
        IntegrationTest_Solve3();
    } else if (args[1] == "pre-gui") {
        PreGui();
    } else {
        if (args[1] != "help") {
            MESSAGE("Unknown action: " << args[1]);
            MESSAGE("");
        }
        
        MESSAGE("Available actions:");
        
        MESSAGE("bin/femu ut (or just bin/femu) -- run unittests");
        MESSAGE("bin/femu wick-example          -- run example wick task");
        MESSAGE("bin/femu solve-1               -- run integration test `solve-1'");
        MESSAGE("bin/femu solve-2               -- run integration test `solve-2'");
        MESSAGE("bin/femu solve-3               -- run integration test `solve-3'");
        MESSAGE("bin/femu pre-gui               -- run pre-gui solution");
        MESSAGE("bin/femu help                  -- show this info");
    }

    return 0;
}
