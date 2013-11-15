#include <ut/tests.h>
#include <util/complex.h>

void UT_Complex_ArithmOperations() {
    ASSERT(EQ(TComplex(1, 0) * TComplex(5, 0), TComplex(5, 0)));
    ASSERT(EQ(ImaginaryUnit, TComplex(0, 1)));
    ASSERT(EQ(TComplex(6) * ImaginaryUnit, TComplex(0, 6)));
    ASSERT(EQ(AbsSquared(1 + ImaginaryUnit), 2));
    ASSERT(EQ(Abs(4 - 3 * ImaginaryUnit), 5));
}

void UT_Complex() {
    MESSAGE("Complex unittest...");
    UT_Complex_ArithmOperations();
    MESSAGE("Complex unittest: ok");
}
