#ifndef PARSEEXCEPTION_H
#define PARSEEXCEPTION_H

#include <exception>

#include <QString>

class ParseException : public std::exception
{
public:
    ParseException(const QString& message);
    ~ParseException();

    QString message() const;

private:
    QString _message;
};

#endif // PARSEEXCEPTION_H
