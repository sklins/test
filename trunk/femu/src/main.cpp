#include <QtCore>
#include <util/exception.h>
#include <ut/tests.h>
#include <ut/integration/wick_example.h>
#include <ut/integration/solve_1.h>

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
    } else {
        if (args[1] != "help") {
            MESSAGE("Unknown action: " << args[1]);
            MESSAGE("");
        }
        
        MESSAGE("Available actions:");
        
        MESSAGE("bin/femu ut (or just bin/femu) -- run unittests");
        MESSAGE("bin/femu wick-example          -- run example wick task");
        MESSAGE("bin/femu solve-1               -- run integration test `solve-1'");
        MESSAGE("bin/femu help                  -- show this info");
    }

    return 0;
}
