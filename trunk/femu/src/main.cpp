#include <QtCore>
#include <ut/tests.h>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // Run unit tests
    RunUnittests();

    return 0;
}
