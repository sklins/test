#include <QtCore>
#include <util/exception.h>
#include <ut/tests.h>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // Run unit tests
    try {
        RunUnittests();
    } catch (const TException &e) {
        e.Display();
    }

    return 0;
}
