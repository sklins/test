#pragma once
#include <QtCore>
#include <QtGui>
#include <QtSvg>
#include "ui_step_2.h"

#include <feyn/feyn_rules.h>

class UI_Step2: public QWidget {
Q_OBJECT
public:
    explicit UI_Step2(QWidget *parent = 0);
    virtual ~UI_Step2();

private:
    Ui::UI_Step2 *ui;
};
