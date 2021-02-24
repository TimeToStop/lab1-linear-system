#ifndef HTMLWRITER_H
#define HTMLWRITER_H

#include <QString>
#include <QStack>
#include <QTextStream>

class HtmlWriter
{
public:
    HtmlWriter();
    ~HtmlWriter();

    void writeDivElement(const QString& styles = "margin: 0px");
    void writeParagraph(const QString& text, const QString& styles = "margin: 0px");
    void writeEndElement();

    QString toHtml() const;

private:
    static const QString _html_pattern;

    QStack<QString> _stack;
    QString _data;
    mutable QTextStream _s;
};

#endif // HTMLWRITER_H
