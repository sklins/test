#pragma once
#include <util/global.h>
#include "diagram.h"

bool CheckIsomorphism(const TDiagram &a, const TDiagram &b);
void FilterDiagrams(const QVector<TDiagram*> *input, QVector<TDiagram*> *output);
