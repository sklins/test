#pragma once
#include "global.h"
#include "prop.h"

class TException {
protected:
    QString Message;

public:
    TException();
    TException(const QString &);

    DECLARE_PROPERTY_GETTER(QString, GetMessage);
    void Display(QTextStream &s) const;
    void Display() const;
};

#define DEFINE_EXCEPTION_CLASS_WITH_BASE_AND_MESSAGE(name, base, defmessage) \
    class name: public base { \
    public: \
        name(): base(defmessage + QString(": ")) {} \
        name(const QString &msg): base(msg) {} \
         \
        template < typename PType > \
        name & operator<<(PType obj) { \
            QTextStream(&Message) << obj; \
            return *this; \
        } \
    };


#define DEFINE_EXCEPTION_CLASS_WITH_BASE(name, base) \
    DEFINE_EXCEPTION_CLASS_WITH_BASE_AND_MESSAGE(name, base, "")


#define DEFINE_EXCEPTION_CLASS_WITH_MESSAGE(name, defmessage) \
    DEFINE_EXCEPTION_CLASS_WITH_BASE_AND_MESSAGE(name, TException, defmessage)


#define DEFINE_EXCEPTION_CLASS(name) \
    DEFINE_EXCEPTION_CLASS_WITH_BASE_AND_MESSAGE(name, TException, defmessage)
