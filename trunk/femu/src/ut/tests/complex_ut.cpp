#include <ut/tests.h>
#include <util/complex.h>

void UT_Complex_ArithmOperations() {
    VERIFY(EQ(TComplex(1, 0) * TComplex(5, 0), TComplex(5, 0)));
    VERIFY(EQ(ImaginaryUnit, TComplex(0, 1)));
    VERIFY(EQ(TComplex(6) * ImaginaryUnit, TComplex(0, 6)));
    VERIFY(EQ(AbsSquared(1 + ImaginaryUnit), 2));
    VERIFY(EQ(Abs(4 - 3 * ImaginaryUnit), 5));
    VERIFY(EQ(1 / ImaginaryUnit, -ImaginaryUnit));
    VERIFY(EQ(TComplex(7, -4) / TComplex(3, 2), TComplex(1, -2)));
    VERIFY(EQ(TComplex(2, 6) / TComplex(5, 10), TComplex(0.56, 0.08)));
    VERIFY(EQ(TComplex(4, 7) / TComplex(2, 1), TComplex(3, 2)));
}

void UT_Complex() {
    MESSAGE("Complex unittest...");
    UT_Complex_ArithmOperations();
    MESSAGE("Complex unittest: ok");
}
