#pragma once
#include <QtCore>
#include <QtGui>
#include <QtSvg>
#include "ui_step_3.h"

#include <feyn/feyn_rules.h>
#include <feyn/generator.h>

class TGeneratingThread: public QThread {
friend class UI_Step3;
Q_OBJECT
public:
    explicit TGeneratingThread(IGenerator *generator): generator(generator) {}
    virtual ~TGeneratingThread() {}

protected:
    /*override*/ void run();

private:
    IGenerator *generator;
    QVector<TDiagram*> Output;
};

class UI_Step3: public QWidget {
Q_OBJECT
public:
    explicit UI_Step3(QWidget *parent = 0);
    virtual ~UI_Step3();

public:
    void Initialize(IGenerator *generator);

private slots:
    void Back();
    void DisplayResults();

private:
    Ui::UI_Step3 *ui;
    TGeneratingThread *thread;
};
