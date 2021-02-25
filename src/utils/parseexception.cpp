#include "parseexception.h"

ParseException::ParseException(const QString& message):
    _message(message)
{
}

ParseException::~ParseException()
{
}

QString ParseException::message() const
{
    return _message;
}
