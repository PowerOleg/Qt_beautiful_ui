#ifndef IVISITOR_H
#define IVISITOR_H

#include <QObject>

class QModelIndex;
class QString;

class IVisitor
{
public:
    virtual ~IVisitor() = default;

    virtual void visit(const QModelIndex& index, const QString& cellText) = 0;
};

#endif // IVISITOR_H
