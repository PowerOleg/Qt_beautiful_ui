#ifndef CHECKBOXITEMDELEGATE_H
#define CHECKBOXITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QWidget>

class CheckBoxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    const int CHECK_ROLE = Qt::CheckStateRole;

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QRect GetCheckboxRect(const QStyleOptionViewItem &option)const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // CHECKBOXITEMDELEGATE_H
