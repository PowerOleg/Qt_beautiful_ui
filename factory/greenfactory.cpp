#include "greenfactory.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QGridLayout>
#include <QTableView>
#include <QStackedWidget>
#include <QSpacerItem>
#include "../esimmodel.h"


GreenFactory::GreenFactory(QObject *parent)
    : Factory(greenPalette, parent)
{}

QDialog* GreenFactory::createDialog(QWidget *parent)
{
    QDialog* d = new QDialog(parent);
    d->setWindowTitle("Добавить профиль");
    d->resize(300, 200);
    /*d->setStyleSheet(
        "background-color: #228B22;"
        "color: white;"
        "font-size: 14px;"
        "font-weight: bold;"
    );*/
    d->setStyleSheet(
            "background-color: " + palette.bgMain + ";"
            "color: " + palette.textColor + ";"
            "font-size: 14px;"
            "font-weight: bold;"
        );
    return d;
}

QLabel* GreenFactory::createLabel(QWidget *parent)
{
    QLabel* l = new QLabel(parent);
    l->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    l->setStyleSheet(
            "background-color: #228B22;"
//            "color: white;"
//           "background-color: " + palette.bgMain + ";"
            "color: " + palette.textColor + ";"
//            "border: 2px solid #228B22;"
            "border: 2px solid" + palette.bgMain + ";"

            "border-radius: 15px;"
            "padding: 4px;"
            "font-size: 14px;"
            "font-weight: bold;"
        );
    return l;
}

QLineEdit* GreenFactory::createLineEdit(QWidget *parent)
{
    QLineEdit* le = new QLineEdit(parent);
    le->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    le->setStyleSheet(
           "background-color: #1B1212;"
           "color: white;"
           "font-size: 14px;"
           "font-weight: bold;"
           "padding: 2px;"
       );
    le->setFixedWidth(200);
    return le;
}

QPushButton* GreenFactory::createPushButton(QWidget *parent)
{
    QPushButton* b = new QPushButton(parent);
//    b->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//    b->setStyleSheet("background-color: #1B1212;"
    b->setStyleSheet(
            "border: 2px solid " + palette.borderColor + ";"
            "border-radius: 10px;"
            "padding: 2px;"
            "background-color: " + palette.bgButton + ";"
            "color: " + palette.textColor + ";"
            "font-size: 14px;"
            "font-weight: bold;"
            // :hover тут не сработает, если стиль задан только на кнопке
        );
    return b;
}

QVBoxLayout* GreenFactory::createVBoxLayout(QWidget *parent)
{
    QVBoxLayout* l = new QVBoxLayout(parent);
    l->setContentsMargins(20, 20, 20, 20);
    l->setSpacing(10);
    return l;
}

QHBoxLayout* GreenFactory::createHBoxLayout(QWidget *parent)
{
    QHBoxLayout* l = new QHBoxLayout(parent);
    l->setContentsMargins(0, 0, 0, 0);
    l->setSpacing(10);
    return l;
}

QGridLayout* GreenFactory::createGridLayout(QWidget *parent)
{
    QGridLayout* l = new QGridLayout(parent);
    l->setContentsMargins(10, 10, 10, 10);
    return l;
}

QFrame* GreenFactory::createFrame(QWidget *parent)
{
    QFrame* f = new QFrame(parent);
    f->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    f->setFrameShape(QFrame::NoFrame);
    return f;
}

QTableView* GreenFactory::createTableView()
{
    QTableView* tableView = new QTableView();
    tableView->setStyleSheet(
            "background-color: " + palette.bgButton + ";"
            "color: " + palette.textColor + ";"
            "font-size: 14px;"
            "font-weight: bold;"
            "border: 1px solid " + palette.bgButton + ";"
            "border-radius: 5px;"
        );
    /*QTableView
    {
        background-color: #228B22;

        color: white;
        font-size: 14px;
        font-weight: bold;
        border: 1px solid #228B22;
        border-radius: 5px;
    }*/
    return tableView;
}

QString Factory::getTableViewStyle() const
{
    const auto &p = palette;
    return
        "QHeaderView { background-color: " + p.bgButton + "; border-radius: 5px; }"
        "QHeaderView::section { background-color: " + p.bgButton + "; color: " + p.textColor + "; font-size: 14px; font-weight: bold; border: 1px solid #1A641A; }"
        "QHeaderView::section:vertical { background-color: " + p.bgButton + "; color: " + p.textColor + "; font-size: 14px; border: 1px solid #1A641A; width: 40px; font-weight: bold; }"
        "QTableView::corner-button { background-color: " + p.bgButton + "; }"
        "QScrollBar:vertical { background-color: " + p.bgButton + "; }"
        "QScrollBar::handle:vertical { background-color: " + p.textColor + "; }"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical, QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background-color: " + p.bgButton + "; }"
        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical { background-color: " + p.textColor + "; }"
        "QScrollBar:horizontal { background-color: " + p.bgButton + "; }"
        "QScrollBar::handle:horizontal { background-color: " + p.textColor + "; }";
}

QStackedWidget* GreenFactory::createStackedWidget(QWidget *parent)
{
    return new QStackedWidget(parent);
}

QSpacerItem* GreenFactory::createSpacer(int w, int h,
                                        QSizePolicy::Policy hPolicy,
                                        QSizePolicy::Policy vPolicy)
{
    return new QSpacerItem(w, h, hPolicy, vPolicy);
}
