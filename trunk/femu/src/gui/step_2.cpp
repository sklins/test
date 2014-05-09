#include "step_1.h"
#include "step_2.h"
#include <util/singleton.h>

UI_Step2::UI_Step2(QWidget *parent): QWidget(parent) {
    ui = new Ui::UI_Step2();
    ui->setupUi(this);

    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    QObject::connect(ui->backButton, SIGNAL(clicked()), this, SLOT(Back()));
}

UI_Step2::~UI_Step2() {
    delete ui;
}

void UI_Step2::Back() {
    hide();
    Singleton<UI_Step1>()->show();
}
