#include "help.h"
#include "step_1.h"
#include <util/singleton.h>

UI_Help::UI_Help(QWidget* parent): QWidget(parent) {
    this->ui = new Ui::UI_Help();
    this->ui->setupUi(this);

    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    QFile helpMessageFile(":/help_message.txt"); // Resource file
    helpMessageFile.open(QIODevice::ReadOnly);
    QTextStream helpMessageStream(&helpMessageFile);
    QString helpMessage = helpMessageStream.readAll();
    helpMessageFile.close();

    this->ui->textBrowser->setText(helpMessage);

    QObject::connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(Back()));
}

UI_Help::~UI_Help() {
    delete this->ui;
}

void UI_Help::Back() {
    hide();
    Singleton<UI_Step1>()->show();
}
