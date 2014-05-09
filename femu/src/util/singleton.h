#pragma once
#include "global.h"

template <class T>
T* Singleton() {
    static T* instance = new T();
    return instance;
}
