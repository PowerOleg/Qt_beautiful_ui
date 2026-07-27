#ifndef CHECKTABLEVISITOR_H
#define CHECKTABLEVISITOR_H

#include "ivisitor.h"

class CheckTableVisitor : public IVisitor
{
public:
    explicit CheckTableVisitor(int dateColumn) : dateColumn(dateColumn) {}

    void visit(const QModelIndex& index, const QString& cellText) override;
private:
    int dateColumn;
    QStringList errors;
};

#endif // CHECKTABLEVISITOR_H
