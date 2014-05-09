#include "step_1.h"
#include "step_2.h"
#include "step_3.h"
#include <util/singleton.h>

UI_Step2::UI_Step2(QWidget *parent): QWidget(parent) {
    ui = new Ui::UI_Step2();
    ui->setupUi(this);

    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    QObject::connect(ui->backButton, SIGNAL(clicked()), this, SLOT(Back()));
    QObject::connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(Next()));
    QObject::connect(ui->loopsLimitCB, SIGNAL(clicked(bool)), this, SLOT(HandleLoopsLimitClick(bool)));
}

UI_Step2::~UI_Step2() {
    delete ui;
}

void UI_Step2::Initialize(TFeynRules *theory) {
    this->theory = theory;
    for (QSet<TParticle*>::ConstIterator i = theory->Particles.begin();
         i != theory->Particles.end(); i++) {
        QSpinBox *spin = new QSpinBox(ui->particles);
        spin->setMinimum(0);
        spin->setMaximum(10);
        spin->setValue(0);
        particleSpinBoxes.insert(*i, spin);
        ui->particlesLayout->addRow((*i)->GetName() + ": ", spin);
    }
}

void UI_Step2::Back() {
    hide();
    Singleton<UI_Step1>()->show();
}

void UI_Step2::Next() {
    TLimitations *limitations = new TLimitations();
    limitations->TotalInteractionsLimit = TOptional<uint32_t>((uint32_t)ui->totalInteractionsLimit->value());

    if (ui->loopsLimitCB->isChecked())
        limitations->LoopsLimit = TOptional<uint32_t>((uint32_t)ui->loopsLimit->value());
    else
        limitations->LoopsLimit = TOptional<uint32_t>();

    if (ui->onlyConnectedCB->isChecked())
        limitations->ConnectedComponentsLimit = TOptional<uint32_t>(1);
    else
        limitations->ConnectedComponentsLimit = TOptional<uint32_t>();

    TGenerator *generator = new TGenerator(this->theory, limitations, ui->kinematicsCB->isChecked());

    for (QSet<TParticle*>::ConstIterator i = theory->Particles.constBegin();
         i != theory->Particles.constEnd(); i++) {
        for (int k = 0; k < particleSpinBoxes[*i]->value(); k++)
            generator->ExternalParticles << (*i);
    }

    generator->IsomorphismCheck = ui->filteringCB->isChecked();

    hide();
    UI_Step3 *s3 = Singleton<UI_Step3>();
    s3->Initialize(generator);
    s3->show();
}

void UI_Step2::HandleLoopsLimitClick(bool val) {
    ui->loopsLimit->setEnabled(val);
}
