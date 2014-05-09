#include <util/global.h>
#include <QtGui>
#include <gui/step_1.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    UI_Step1 step_1;
    step_1.show();

    return app.exec();
}
