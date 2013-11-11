#include <ut/tests.h>
#include <util/num.h>

void UT_Num_Compare() {
    ASSERT(Compare(1, 3, 1) == LESS_THAN);
    ASSERT(Compare(7, 6, 3) == EQUALS_TO);
    ASSERT(Compare(9, 5, 3) == GREATER_THAN);
}

void UT_Num_Operations() {
    ASSERT(EQ(Sqrt(4), 2));
    ASSERT(EQ(Sqrt(2), 1.41, 0.01));
    ASSERT(EQ(Sin(0), 0));
    ASSERT(EQ(Cos(0), 1));
    ASSERT(EQ(Sin(NumPi), 0));
    ASSERT(EQ(Sin(NumPi / 2), 1));
    ASSERT(EQ(Cos(NumPi), -1));
}

void UT_Num() {
    MESSAGE("Num unittest...");
    UT_Num_Compare();
    UT_Num_Operations();
    MESSAGE("Num unittest: ok");
}
