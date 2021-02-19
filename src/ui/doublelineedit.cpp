#include "doublelineedit.h"

#include <QMessageBox>
#include <QDoubleValidator>

#include "../utils/utils.h"

DoubleLineEdit::DoubleLineEdit(double value, QWidget* parent):
    QLineEdit("0", parent),
    _previous_value(0)
{
    connect(this, &QLineEdit::textEdited, this, &DoubleLineEdit::onValueEdited);
    setValidator(new QDoubleValidator(this));
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedWidth(40);
    setValue(value);
}

DoubleLineEdit::~DoubleLineEdit()
{
}

void DoubleLineEdit::setValue(double value)
{
    if(!::nearlyEqual(_previous_value, value))
    {
        setText(QString::number(value));
        _previous_value = value;
    }
}

void DoubleLineEdit::onValueEdited(const QString& text)
{
    if (text.isEmpty()) return;

    bool ok = true;
    double value = text.toDouble(&ok);

    if (!ok)
    {
        value = 0;
        QMessageBox::critical(this, "Error", "Value is not parsed correctly. Assume 0");
    }

    _previous_value = value;
    emit valueEdited(value);
}
