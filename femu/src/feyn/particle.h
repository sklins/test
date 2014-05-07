#pragma once
#include <util/global.h>

enum ELineShape {
    LS_NORMAL, LS_DASHED, LS_WAVE, LS_DOTTED
};

class TParticle
{
public:
    TParticle(QString name, ELineShape lineShape) : Name(name), LineShape(lineShape) {}

public:
    ELineShape GetLineShape() { return this->LineShape;}
    QString GetName() const { return this->Name; }
    
private:
    QString Name;
    ELineShape LineShape;
};
