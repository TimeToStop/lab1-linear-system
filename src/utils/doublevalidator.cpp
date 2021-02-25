#include "doublevalidator.h"

DoubleValidator::DoubleValidator(QObject *parent):
    QDoubleValidator(parent)
{
}

DoubleValidator::~DoubleValidator()
{
}

QValidator::State DoubleValidator::validate(QString& input, int& pos) const
{
    QString temp = input;
    temp.replace('.', ',');
    QValidator::State state = QDoubleValidator::validate(temp, pos);

    if(state == QValidator::State::Intermediate)
    {
        return QValidator::State::Invalid;
    }

    return state;
}
