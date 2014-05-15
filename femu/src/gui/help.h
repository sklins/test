#pragma once
#include <QtCore>
#include <QtGui>
#include <QtSvg>
#include "ui_help.h"

#include <feyn/feyn_rules.h>

class UI_Help: public QWidget {
Q_OBJECT
public:
    explicit UI_Help(QWidget *parent = 0);
    virtual ~UI_Help();

private slots:
    void Back();

private:
    Ui::UI_Help *ui;
};
