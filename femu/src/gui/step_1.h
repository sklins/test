#pragma once
#include <QtCore>
#include <QtGui>
#include <QtSvg>
#include "ui_step_1.h"

#include <feyn/feyn_rules.h>

class UI_Step1: public QWidget {
Q_OBJECT
public:
    explicit UI_Step1(QWidget *parent = 0);
    virtual ~UI_Step1();

private:
    void ImportTheories();
    void ShowTheories();

private slots:
    void HandleClick(QListWidgetItem*);
    void Next();

private:
    Ui::UI_Step1 *ui;
    QHash<QString, TFeynRules*> theories;
    QVector<QSvgWidget*> svgWidgets;
};
