#include "num.h"
#include <math.h>

TCmpRes Compare(TNum a, TNum b, TNum eps) {
    if (a < b - eps) return LESS_THAN;
    if (a > b + eps) return GREATER_THAN;
    return EQUALS_TO;
}

IMPLEMENT_PRECISE_COMPARATORS(TNum, TNum, Compare)

TNum Pow(TNum a, TNum b) {
    return pow(a, b);
}

TNum Sqrt(TNum a) {
    return sqrt(a);
}

TNum Sin(TNum a) {
    return sin(a);
}

TNum Cos(TNum a) {
    return cos(a);
}

TNum ArcSin(TNum a) {
    return asin(a);
}

TNum ArcCos(TNum a) {
    return acos(a);
}
