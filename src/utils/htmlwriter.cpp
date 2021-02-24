#include "htmlwriter.h"

#include <QIODevice>

const QString HtmlWriter::_html_pattern =
        "<!DOCTYPE html><html><head></head><body>%1</body></html>"
;

HtmlWriter::HtmlWriter():
    _data(),
    _s(&_data, QIODevice::WriteOnly)
{   
}

HtmlWriter::~HtmlWriter()
{
}

void HtmlWriter::writeDivElement(const QString &styles)
{
    _s << QStringLiteral("<div style=\"%1\">").arg(styles);
    _stack.push("</div>");
}

void HtmlWriter::writeParagraph(const QString &text, const QString &styles)
{
    _s << QStringLiteral("<p style=\"%1\">").arg(styles)
            << text
       << QStringLiteral("</p>");
}

void HtmlWriter::writeEndElement()
{
    if (!_stack.isEmpty())
    {
        _s << _stack.top();
    }
}

QString HtmlWriter::toHtml() const
{
    _s.flush();
    return _html_pattern.arg(_data);
}
