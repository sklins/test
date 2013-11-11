#pragma once
#include "compare.h"
#include "arithm.h"
#include "num.h"

struct TComplex {
    TNum Re, Im;
    TComplex(TNum = 0, TNum = 0);
};

const TComplex ImaginaryUnit(0, 1);

DECLARE_EQUALITY_TESTS(const TComplex &)
DECLARE_PRECISE_EQUALITY_TESTS(const TComplex, TNum, StandardPrecision)
DECLARE_UNARY_PLUS_AND_MINUS(TComplex)
DECLARE_ARITHMETIC_OPERATION_WITH_SHORTCUT(TComplex, +, +=, TComplex)
DECLARE_ARITHMETIC_OPERATION_WITH_SHORTCUT(TComplex, -, -=, TComplex)
DECLARE_ARITHMETIC_OPERATION_WITH_SHORTCUT(TComplex, *, *=, TComplex)
DECLARE_ARITHMETIC_OPERATION_WITH_SHORTCUT(TComplex, /, /=, TComplex)

TEqTestRes EqTest(const TComplex &, const TComplex &, TNum = StandardPrecision);
TComplex Addition(const TComplex &, const TComplex &);
TComplex Subtraction(const TComplex &, const TComplex &);
TComplex Multiplication(const TComplex &, const TComplex &);
TComplex Divizion(const TComplex &, const TComplex &);

TNum AbsSquared(const TComplex &);
TNum Abs(const TComplex &);
TNum Arg(const TComplex &);
TNum Re(const TComplex &);
TNum Im(const TComplex &);

