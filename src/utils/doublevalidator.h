#ifndef DOUBLEVALIDATOR_H
#define DOUBLEVALIDATOR_H

#include <QDoubleValidator>

class DoubleValidator : public QDoubleValidator
{
public:
    DoubleValidator(QObject* parent = nullptr);
    virtual ~DoubleValidator();

    virtual QValidator::State validate(QString& input, int& pos) const override;
};

#endif // DOUBLEVALIDATOR_H
