#include "step_2.h"
#include <util/singleton.h>

UI_Step2::UI_Step2(QWidget *parent): QWidget(parent) {
    ui = new Ui::UI_Step2();
    ui->setupUi(this);

    move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

UI_Step2::~UI_Step2() {
    delete ui;
}
