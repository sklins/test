#pragma once
#include "compare.h"

typedef double TNum;

template < typename T >
TNum Num(T v) {
    return v;
}

const TNum StandardPrecision = 1e-9;
const TNum NumPi = M_PI;
const TNum NumE = M_E;

TCmpRes Compare(TNum, TNum, TNum = StandardPrecision);
DECLARE_PRECISE_COMPARATORS(TNum, TNum, StandardPrecision)

TNum Pow(TNum, TNum);
TNum Sqrt(TNum);
TNum Exp(TNum);
TNum Sin(TNum);
TNum Cos(TNum);
TNum ArcSin(TNum);
TNum ArcCos(TNum);
