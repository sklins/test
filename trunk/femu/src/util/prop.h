#pragma once
#include "global.h"

#define DECLARE_PROPERTY_GETTER(type, function) \
    type function() const;

#define IMPLEMENT_PROPERTY_GETTER(class, type, function, variable) \
    type class::function() const { return variable; }


#define DECLARE_PROPERTY_SETTER(type, function) \
    void function(const type &);

#define IMPLEMENT_PROPERTY_SETTER(class, type, function, variable) \
    void class::function(const type &value) { variable = value; }


#define DECLARE_PROPERTY(type, getfunc, setfunc) \
    DECLARE_PROPERTY_GETTER(type, getfunc) \
    DECLARE_PROPERTY_SETTER(type, setfunc)

#define IMPLEMENT_PROPERTY(class, type, getfunc, setfunc, variable) \
    IMPLEMENT_PROPERTY_GETTER(class, type, getfunc, variable) \
    IMPLEMENT_PROPERTY_SETTER(class, type, setfunc, variable)

