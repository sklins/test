#include "step_2.h"
#include "step_3.h"
#include <util/singleton.h>

void TGeneratingThread::run() {
    generator->Generate(&Output);
}

UI_Step3::UI_Step3(QWidget *parent): QWidget(parent) {
    ui = new Ui::UI_Step3();
    ui->setupUi(this);

    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    ui->scrollArea->setBackgroundRole(QPalette::Dark);

    QObject::connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->backButton, SIGNAL(clicked()), this, SLOT(Back()));
}

UI_Step3::~UI_Step3() {
    delete ui;
}

void UI_Step3::Initialize(IGenerator *generator) {
    ui->progressBar->setValue(50);

    foreach (QWidget *widget, ui->diagramsArea->findChildren<QWidget*>()) {
        delete widget;
    }

    thread = new TGeneratingThread(generator);
    thread->start(QThread::HighestPriority);
    QObject::connect(thread, SIGNAL(finished()), this, SLOT(DisplayResults()));
}

void UI_Step3::Back() {
    hide();
    Singleton<UI_Step2>()->show();
}

const int ROWS = 3;
const int W = 540;
const int H = 540;

void UI_Step3::DisplayResults() {
    ui->progressBar->setValue(100);

    QVector<TDiagram*> *res = &thread->Output;

    for (int i = 0; i < res->size(); i++) {
        QSvgWidget *w = new QSvgWidget(this);
        w->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        w->setFixedSize(W / ROWS, H / ROWS);

        QByteArray data = res->at(i)->GenerateImageData();
        w->load(data);

        ui->diagramsLayout->addWidget(w, i / ROWS, i % ROWS);
    }
}
