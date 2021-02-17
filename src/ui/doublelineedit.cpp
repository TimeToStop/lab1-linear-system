#include "doublelineedit.h"

#include <QMessageBox>

DoubleLineEdit::DoubleLineEdit(QWidget* parent):
    QLineEdit(parent)
{
    connect(this, &QLineEdit::textEdited, this, &DoubleLineEdit::onValueEdited);
}

DoubleLineEdit::~DoubleLineEdit()
{
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

    emit valueEdited(value);
}
