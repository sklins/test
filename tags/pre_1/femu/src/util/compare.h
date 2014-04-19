#pragma once
#include "global.h"

typedef bool TEqTestRes;
const TEqTestRes OBJECTS_ARE_EQUAL = true;
const TEqTestRes OBJECTS_DIFFER = false;

#define DECLARE_EQUALITY_TESTS(type) \
    bool operator==(type a, type b); \
    bool operator!=(type a, type b);

#define IMPLEMENT_EQUALITY_TESTS(type, function) \
    bool operator==(type a, type b) { return function(a, b) == OBJECTS_ARE_EQUAL; } \
    bool operator!=(type a, type b) { return function(a, b) == OBJECTS_DIFFER; }

#define DECLARE_PRECISE_EQUALITY_TESTS(type, epsType, eps0) \
    bool EQ(type a, type b, epsType eps = eps0); \
    bool NE(type a, type b, epsType eps = eps0);

#define IMPLEMENT_PRECISE_EQUALITY_TESTS(type, epsType, function) \
    bool EQ(type a, type b, epsType eps) { return function(a, b, eps) == OBJECTS_ARE_EQUAL; } \
    bool NE(type a, type b, epsType eps) { return function(a, b, eps) == OBJECTS_DIFFER; }

typedef int8_t TCmpRes;
const TCmpRes LESS_THAN = -1;
const TCmpRes EQUALS_TO = 0;
const TCmpRes GREATER_THAN = 1;

#define DECLARE_COMPARATORS(type) \
    bool operator==(type a, type b); \
    bool operator!=(type a, type b); \
    bool operator<=(type a, type b); \
    bool operator>=(type a, type b); \
    bool operator< (type a, type b); \
    bool operator> (type a, type b);

#define IMPLEMENT_COMPARATORS(type, function) \
    bool operator==(type a, type b) { return function(a, b) == 0; } \
    bool operator!=(type a, type b) { return function(a, b) != 0; } \
    bool operator<=(type a, type b) { return function(a, b) <= 0; } \
    bool operator>=(type a, type b) { return function(a, b) >= 0; } \
    bool operator< (type a, type b) { return function(a, b) <  0; } \
    bool operator> (type a, type b) { return function(a, b) >  0; }

#define DECLARE_PRECISE_COMPARATORS(type, epsType, eps0) \
    bool EQ(type a, type b, epsType eps = eps0); \
    bool NE(type a, type b, epsType eps = eps0); \
    bool LE(type a, type b, epsType eps = eps0); \
    bool GE(type a, type b, epsType eps = eps0); \
    bool LT(type a, type b, epsType eps = eps0); \
    bool GT(type a, type b, epsType eps = eps0);

#define IMPLEMENT_PRECISE_COMPARATORS(type, epsType, function) \
    bool EQ(type a, type b, epsType eps) { return function(a, b, eps) == 0; } \
    bool NE(type a, type b, epsType eps) { return function(a, b, eps) != 0; } \
    bool LE(type a, type b, epsType eps) { return function(a, b, eps) <= 0; } \
    bool GE(type a, type b, epsType eps) { return function(a, b, eps) >= 0; } \
    bool LT(type a, type b, epsType eps) { return function(a, b, eps) <  0; } \
    bool GT(type a, type b, epsType eps) { return function(a, b, eps) >  0; }

