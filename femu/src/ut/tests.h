#pragma once
#include "ut_tools.h"

// List of UT functions
void UT_Num();

// Run all UT functions
void RunUnittests() {
    UT_Num();
    MESSAGE("Unittests: OK");
}
