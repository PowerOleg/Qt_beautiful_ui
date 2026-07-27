#include "checktablevisitor.h"
#include <QString>
#include <QModelIndex>
#include <QStringList>
#include <QDate>

void CheckTableVisitor::visit(const QModelIndex& index, const QString& cellText)
{
    if (index.column() != dateColumn)
        return;

    if (cellText.isEmpty())
        return;

    QDate date = QDate::fromString(cellText, Qt::ISODate);
/*    if (!date.isValid())
    {
        errors << QString("Неверный формат даты в строке %1: '%2'")
                     .arg(index.row()).arg(cellText);
        return;
    }

    if (date.year() < 2024)
    {
        errors << QString("Устаревшая дата в строке %1: %2 (год %3)")
                     .arg(index.row()).arg(cellText).arg(date.year());
    }*/
}
