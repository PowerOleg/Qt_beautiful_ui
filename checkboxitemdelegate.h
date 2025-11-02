#ifndef CHECKBOXITEMDELEGATE_H
#define CHECKBOXITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QModelIndex>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QStyleOptionFrame>
#include <QRect>
#include <QStyle>
#include <QStyleOption>
#include <QStyleOptionButton>
#include <QApplication>
#include <QAbstractItemModel>
#include <QMouseEvent>
#include <QEvent>

class CheckBoxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    const int CHECK_ROLE = Qt::CheckStateRole;

    // dont't let the default QStyledItemDelegate create the true/false combobox
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        (void)parent;
        (void)option;
        (void)index;
        return nullptr;
    }


    QRect GetCheckboxRect(const QStyleOptionViewItem &option)const
    {
        QStyleOptionButton opt_button;
        opt_button.QStyleOption::operator=(option);
        QRect sz = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &opt_button);//subElementRect(QStyle::SE_ViewItemCheckIndicator, &opt_button);
        QRect r = option.rect;
        // center 'sz' within 'r'
        int dx = (r.width() - sz.width())/2;
        int dy = (r.height()- sz.height())/2;
        r.setTopLeft(r.topLeft() + QPoint(dx,dy));
        r.setWidth(sz.width());
        r.setHeight(sz.height());

        return r;
    }


    // click event
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
    {
        if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent* pME = static_cast<QMouseEvent*>(event);
            if(pME->button() == Qt::LeftButton)
            {
                QRect ro = GetCheckboxRect(option);
                QPoint pte = pME->pos();
                if(ro.contains(pte) )
                {
                    bool value = index.data(CHECK_ROLE).toBool();

                    // invert checkbox state
                    model->setData(index, !value, CHECK_ROLE);

                    return true;
                }
            }
        }

        return QStyledItemDelegate::editorEvent(event, model, option, index);
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QStyleOptionButton cbOpt;
        cbOpt.rect = GetCheckboxRect(option);

        bool isChecked = index.data(CHECK_ROLE).toBool();
        if (isChecked)
        {
            cbOpt.state |= QStyle::State_On;
        }
        else
        {
            cbOpt.state |= QStyle::State_Off;
        }

        QVariant enabled = index.data(Qt::ItemIsEnabled);
        if(enabled.isNull() || enabled.toBool() )
        {
            cbOpt.state |= QStyle::State_Enabled;
        }

        QApplication::style()->drawControl(QStyle::CE_CheckBox, &cbOpt, painter);
    }
};

#endif // CHECKBOXITEMDELEGATE_H
