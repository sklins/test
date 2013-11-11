#pragma once
#include "global.h"

#define DECLARE_ARITHMETIC_OPERATION(typeR, op, typeA, typeB) \
    typeR operator op (const typeA &, const typeB &);

#define IMPLEMENT_ARITHMETIC_OPERATION(typeR, op, typeA, typeB, function) \
    typeR operator op (const typeA &a, const typeB &b) { return function(a, b); }


#define DECLARE_ARITHMETIC_BIDIRECTIONAL_OPERATION(typeR, op, typeA, typeB) \
    typeR operator op (const typeA &, const typeB &); \
    typeR operator op (const typeB &, const typeA &);

#define IMPLEMENT_ARITHMETIC_BIDIRECTIONAL_OPERATION(typeR, op, typeA, typeB, function) \
    typeR operator op (const typeA &a, const typeB &b) { return function(a, b); } \
    typeR operator op (const typeB &b, const typeA &a) { return function(a, b); }


#define DECLARE_ARITHMETIC_OPERATION_WITH_SHORTCUT(typeR, op, shortcut, typeO) \
    typeR operator op (const typeR &, const typeO &); \
    typeR & operator shortcut (typeR &r, const typeO &o);

#define IMPLEMENT_ARITHMETIC_OPERATION_WITH_SHORTCUT(typeR, op, shortcut, typeO, function) \
    typeR operator op (const typeR &r, const typeO &o) { return function(r, o); } \
    typeR & operator shortcut (typeR &r, const typeO &o) { r = function(r, o); return r; }


#define DECLARE_ARITHMETIC_BIDIRECTIONAL_OPERATION_WITH_SHORTCUT(typeR, op, shortcut, typeO) \
    typeR operator op (const typeR &, const typeO &); \
    typeR operator op (const typeO &, const typeR &); \
    typeR & operator shortcut (typeR &r, const typeO &o);

#define IMPLEMENT_ARITHMETIC_BIDIRECTIONAL_OPERATION_WITH_SHORTCUT(typeR, op, shortcut, typeO, function) \
    typeR operator op (const typeR &r, const typeO &o) { return function(r, o); } \
    typeR operator op (const typeO &o, const typeR &r) { return function(r, o); } \
    typeR & operator shortcut (typeR &r, const typeO &o) { r = function(r, o); return r; }


#define DECLARE_UNARY_PLUS_AND_MINUS(type) \
    type operator+(const type &); \
    type operator-(const type &);

#define IMPLEMENT_UNARY_PLUS_AND_MINUS(type) \
    type operator+(const type &x) { return x; } \
    type operator-(const type &x) { return type() - x; }
