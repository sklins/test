#include "exception.h"

TException::TException(): Message() {}
TException::TException(const QString &message): Message(message) {}

IMPLEMENT_PROPERTY_GETTER(TException, QString, GetMessage, Message);

void TException::Display(QTextStream &stream) const {
    stream << "UNCAUGHT EXCEPTION " << Message << "\n";
}

void TException::Display() const {
    QTextStream errorstream(stderr);
    Display(errorstream);
}
