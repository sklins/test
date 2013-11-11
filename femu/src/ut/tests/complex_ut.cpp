#include <ut/tests.h>
#include <util/complex.h>

void UT_Complex_ArithmOperations() {
    ASSERT(TComplex(1, 0) * TComplex(5, 0) == TComplex(5, 0));
    ASSERT(ImaginaryUnit == TComplex(0, 1));
    ASSERT(TComplex(6) * ImaginaryUnit == TComplex(0, 6));
    ASSERT(AbsSquared(1 + ImaginaryUnit) == 2);
    ASSERT(Abs(4 - 3 * ImaginaryUnit) == 5);
}

void UT_Complex() {
    MESSAGE("Complex unittest...");
    UT_Complex_ArithmOperations();
    MESSAGE("Complex unittest: ok");
}
