#pragma once
#include <util/global.h>
#include "diagram.h"

class ITask {
public:
    /*abstract*/ void Solve(QVector<TDiagram*> *output) = 0;
};
