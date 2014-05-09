#pragma once
#include "global.h"

template <class T>
T* Singleton() {
    static QScopedPointer<T> ptr;
    if (ptr.isNull())
        ptr.reset(new T());
    return ptr.take();
}
