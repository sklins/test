#include <util/global.h>
#include <util/singleton.h>
#include <QtGui>
#include <gui/step_1.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Singleton<UI_Step1>()->show();

    return app.exec();
}
