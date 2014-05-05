#pragma once
#include "global.h"

template <typename T>
class TOptional {
public:
    TOptional(): H(false), V() {}
    TOptional(const T& val): H(true), V(val) {}

    bool HasValue() const {
        return H;
    }

    const T& Get() const {
        ASSERT(HasValue());
        return V;
    }

    T& Get() {
        ASSERT(HasValue());
        return V;
    }

    const T& operator*() const { return Get(); }
    T& operator*() { return Get(); }

    const T* operator->() const { return &Get(); }
    T* operator->() { return &Get(); }

private:
    bool H;
    T V;
};
