#include "exception.h"

TException::TException(): Message() {}
TException::TException(const QString &message): Message(message) {}

IMPLEMENT_PROPERTY_GETTER(TException, QString, GetMessage, Message);
