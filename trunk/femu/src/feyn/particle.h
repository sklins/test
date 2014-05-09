#pragma once
#include <util/global.h>

enum ELineStyle {
    LS_NORMAL, LS_DASHED, LS_WAVE, LS_DOTTED
};

class TParticle
{
public:
    TParticle(QString name, ELineStyle lineShape) : Name(name), LineShape(lineShape) {}

public:
    ELineStyle GetLineShape() { return this->LineShape;}
    QString GetName() const { return this->Name; }
    
private:
    QString Name;
    ELineStyle LineShape;
};
