#include "doublelineedit.h"

#include <QMessageBox>
#include <QDoubleValidator>

#include "../utils/utils.h"
#include "../utils/doublevalidator.h"

DoubleLineEdit::DoubleLineEdit(double value, QWidget* parent):
    QLineEdit("0", parent)
{
    connect(this, &QLineEdit::textEdited, this, &DoubleLineEdit::onValueEdited);
    setValidator(new DoubleValidator(this));
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedWidth(40);
    setValue(value);
}

DoubleLineEdit::~DoubleLineEdit()
{
}

void DoubleLineEdit::setValue(double value)
{
    setText(QString::number(value));
}

void DoubleLineEdit::onValueEdited(const QString& text)
{
    double value = 0;
    QString new_text = text;

    if (text.size() > 0 && text[text.size() - 1].toLower() == 'e') new_text.chop(1);

    if (new_text.isEmpty()) return;
    if (new_text == "-") return;

    bool ok = true;
    new_text.replace(',', '.');
    value = new_text.toDouble(&ok);

    if (!ok)
    {
        value = 0;
        QMessageBox::critical(this, "Error", "Value is not parsed correctly. Assume 0");
    }

    emit valueEdited(value);
}
