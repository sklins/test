#pragma once
#include "global.h"
#include "prop.h"

class TException {
private:
    QString Message;

public:
    TException();
    TException(const QString &);

    DECLARE_PROPERTY_GETTER(QString, GetMessage);
};

#define DECLARE_EXCEPTION_CLASS_WITH_BASE(name, base) \
    class name: public base { \
    public: \
        name(); \
        name(const QString &); \
    }

#define IMPLEMENT_EXCEPTION_CLASS_WITH_BASE(name, base) \
    name::name(): base() {} \
    name::name(const QString &message): base(message) {}


#define DECLARE_EXCEPTION_CLASS(name) DECLARE_EXCEPTION_CLASS_WITH_BASE(name, TException)
#define IMPLEMENT_EXCEPTION_CLASS(name) IMPLEMENT_EXCEPTION_CLASS_WITH_BASE(name, TException)
