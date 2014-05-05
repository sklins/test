#include <ut/tests.h>
#include <util/num.h>

void UT_Num_Compare() {
    VERIFY(Compare(1, 3, 1) == LESS_THAN);
    VERIFY(Compare(7, 6, 3) == EQUALS_TO);
    VERIFY(Compare(9, 5, 3) == GREATER_THAN);
}

void UT_Num_Operations() {
    VERIFY(EQ(Sqrt(4), 2));
    VERIFY(EQ(Sqrt(2), 1.41, 0.01));
    VERIFY(EQ(Sin(0), 0));
    VERIFY(EQ(Cos(0), 1));
    VERIFY(EQ(Sin(NumPi), 0));
    VERIFY(EQ(Sin(NumPi / 2), 1));
    VERIFY(EQ(Cos(NumPi), -1));
    VERIFY(EQ(Exp(0), 1));
    VERIFY(EQ(Exp(1), NumE));
    VERIFY(EQ(Exp(-1), 1 / NumE));
}

void UT_Num() {
    MESSAGE("Num unittest...");
    UT_Num_Compare();
    UT_Num_Operations();
    MESSAGE("Num unittest: ok");
}
