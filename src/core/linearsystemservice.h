#ifndef LINEARSYSTEMSERVICE_H
#define LINEARSYSTEMSERVICE_H

#include <QObject>

class LinearSystemService : public QObject
{
    Q_OBJECT
public:
    explicit LinearSystemService(QObject* parent = nullptr);
    virtual ~LinearSystemService();

signals:

};

#endif // LINEARSYSTEMSERVICE_H
