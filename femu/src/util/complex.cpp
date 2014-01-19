#include "complex.h"

TComplex::TComplex(TNum re, TNum im): Re(re), Im(im) {}

IMPLEMENT_EQUALITY_TESTS(const TComplex &, EqTest)
IMPLEMENT_PRECISE_EQUALITY_TESTS(const TComplex &, TNum, EqTest)
IMPLEMENT_UNARY_PLUS_AND_MINUS(TComplex)
IMPLEMENT_ARITHMETIC_OPERATION_WITH_SHORTCUT(TComplex, +, +=, TComplex, Addition)
IMPLEMENT_ARITHMETIC_OPERATION_WITH_SHORTCUT(TComplex, -, -=, TComplex, Subtraction)
IMPLEMENT_ARITHMETIC_OPERATION_WITH_SHORTCUT(TComplex, *, *=, TComplex, Multiplication)
IMPLEMENT_ARITHMETIC_OPERATION_WITH_SHORTCUT(TComplex, /, /=, TComplex, Divizion)

TEqTestRes EqTest(const TComplex &a, const TComplex &b, TNum eps) {
    if (EQ(a.Re, b.Re, eps) && EQ(a.Im, b.Im, eps))
        return OBJECTS_ARE_EQUAL;
    else return OBJECTS_DIFFER;
}

TComplex Addition(const TComplex &a, const TComplex &b) {
    return TComplex(a.Re + b.Re, a.Im + b.Im);
}

TComplex Subtraction(const TComplex &a, const TComplex &b) {
    return TComplex(a.Re - b.Re, a.Im - b.Im);
}

TComplex Multiplication(const TComplex &a, const TComplex &b) {
    return TComplex(a.Re * b.Re - a.Im * b.Im, a.Re * b.Im + a.Im * b.Re);
}

TComplex Divizion(const TComplex &a, const TComplex &b) {
	return TComplex ((a.Re * b.Re + a.Im * b.Im) / (b.Re * b.Re + b.Im * b.Im), (a.Im * b.Re - a.Re * b.Im) / (b.Re * b.Re + b.Im * b.Im));
}

TNum AbsSquared(const TComplex &x) {
    return Pow(x.Re, 2) + Pow(x.Im, 2);
}

TNum Abs(const TComplex &x) {
    return Sqrt(AbsSquared(x));
}

TNum Arg(const TComplex &x) {
    // TODO: implement
    NOT_IMPLEMENTED;
}

TNum Re(const TComplex &x) {
    return x.Re;
}

TNum Im(const TComplex &x) {
    return x.Im;
}

TComplex Conjugate(const TComplex &x) {
    return TComplex(Re(x), -Im(x));
}

TComplex ComplexExp(const TComplex &x) {
    // TODO: implement
    NOT_IMPLEMENTED;
}

