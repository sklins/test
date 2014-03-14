#include <QtCore>
#include <util/exception.h>
#include <ut/tests.h>

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
    } else {
        if (args[1] != "help") {
            MESSAGE("Unknown action: " << args[1]);
            MESSAGE("");
        }
        
        MESSAGE("Available actions:");
        
        MESSAGE("bin/femu ut (or just bin/femu) -- run unittests");
        MESSAGE("bin/femu help                  -- show this info");
    }

    return 0;
}
