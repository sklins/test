#pragma once
#include "global.h"

template <class T>
class TSingleton {
    static T* Handle(bool sw, T* val) {
        static T* instance = new T();
        if (sw) {
            instance = val;
            return NULL;
        } else return instance;
    }

public:
    static T* Instance() {
        return Handle(false, NULL);
    }

    static void Switch(T* val) {
        Handle(true, val);
    }
};

template <class T>
T* Singleton() {
    return TSingleton<T>::Instance();
}
