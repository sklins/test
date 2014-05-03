#include <ut/tests.h>
#include "wick_example.h"
#include <wick/wick_slot.h>
#include <wick/wick_task.h>
#include <feyn/diagram.h>

const int N = 6; // Max interaction vertexes

void GenerateContractionsForSampleTask() {
    MESSAGE("Generating an instance of TWickTask...");

    TParticle scalarBoson("scalar boson", LS_NORMAL);

    TWickSlot inputBoson(1, 0, false, true);
    inputBoson.InitializeFreedomDegree(&scalarBoson, 1);

    TWickSlot ouputBoson(1, 0, false, true);
    ouputBoson.InitializeFreedomDegree(&scalarBoson, 1);

    QVector<TWickSlot> F4Vertexes;
    for (int i = 0; i < N; i++) {
        F4Vertexes << TWickSlot(2, 0, true, false);
        F4Vertexes.back().InitializeFreedomDegree(&scalarBoson, 4);
    }

    QVector<TDiagram*> res;

    TWickTask task;
    task.Slots << inputBoson << ouputBoson;
    for (int i = 0; i < N; i++) {
        task.Slots << F4Vertexes[i];
        int ln = res.size();
        MESSAGE("Solving for " << (i + 1) << " interactions..");
        task.Solve(&res, true);
        MESSAGE("Got " << res.size() - ln << " diagrams");
    }

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
