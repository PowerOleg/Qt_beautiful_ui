#include "bluefactory.h"
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


BlueSquareFactory::BlueSquareFactory(QObject *parent)
    : Factory(bluePalette, parent)
{}

QDialog* BlueSquareFactory::createDialog(QWidget *parent)
{
    QDialog* d = new QDialog(parent);
    d->setWindowTitle("Добавить профиль");
    d->resize(300, 200);
    d->setStyleSheet(
            "background-color: " + palette.bgMain + ";"
            "color: " + palette.textColor + ";"
            "font-size: 14px;"
            "font-weight: bold;"
        );
    return d;
}

QLabel* BlueSquareFactory::createLabel(QWidget *parent)
{
    QLabel* l = new QLabel(parent);
    l->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    l->setStyleSheet(
           "background-color: " + palette.bgButton + ";"
            "color: " + palette.textColor + ";"
            "border: 2px solid" + palette.bgMain + ";"
            "border-radius: 1px;"
            "padding: 4px;"
            "font-size: 14px;"
            "font-weight: bold;"
        );
    return l;
}

QLineEdit* BlueSquareFactory::createLineEdit(QWidget *parent)
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

QPushButton* BlueSquareFactory::createPushButton(QWidget *parent)
{
    QPushButton* b = new QPushButton(parent);
    b->setStyleSheet(
            "border: 2px solid " + palette.borderColor + ";"
            "border-radius: 1px;"
            "padding: 2px;"
            "background-color: " + palette.bgButton + ";"
            "color: " + palette.textColor + ";"
            "font-size: 14px;"
            "font-weight: bold;"
        );
    return b;
}

QVBoxLayout* BlueSquareFactory::createVBoxLayout(QWidget *parent)
{
    QVBoxLayout* l = new QVBoxLayout(parent);
    l->setContentsMargins(20, 20, 20, 20);
    l->setSpacing(10);
    return l;
}

QHBoxLayout* BlueSquareFactory::createHBoxLayout(QWidget *parent)
{
    QHBoxLayout* l = new QHBoxLayout(parent);
    l->setContentsMargins(0, 0, 0, 0);
    l->setSpacing(10);
    return l;
}

QGridLayout* BlueSquareFactory::createGridLayout(QWidget *parent)
{
    QGridLayout* l = new QGridLayout(parent);
    l->setContentsMargins(10, 10, 10, 10);
    return l;
}

QFrame* BlueSquareFactory::createFrame(QWidget *parent)
{
    QFrame* f = new QFrame(parent);
    f->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    f->setFrameShape(QFrame::NoFrame);
    return f;
}

QTableView* BlueSquareFactory::createTableView()
{
    QTableView* tableView = new QTableView();
    tableView->setStyleSheet(
            "background-color: " + palette.bgButton + ";"
            "color: " + palette.textColor + ";"
            "font-size: 14px;"
            "font-weight: bold;"
            "border: 1px solid " + palette.bgButton + ";"
            "border-radius: 1px;"
        );

    return tableView;
}

QString BlueSquareFactory::getTableViewStyle() const
{
    const auto &p = palette;
        return
            "QHeaderView { background-color: " + p.bgButton + "; border-radius: 1px; }"
            "QHeaderView::section { "
                "background-color: " + p.bgButton + ";"
                "color: " + p.textColor + ";"
                "font-size: 14px;"
                "font-weight: bold;"
                "border: 1px solid " + p.borderColor + ";"
                "padding: 4px;"
            "}"
            "QHeaderView::section:vertical { "
                "background-color: " + p.bgButton + ";"
                "color: " + p.textColor + ";"
                "font-size: 14px;"
                "border: 1px solid " + p.borderColor + ";"
                "width: 40px;"
                "font-weight: bold;"
                "padding: 4px;"
            "}"
            "QTableView::corner-button { background-color: " + p.bgButton + "; }"
            "QScrollBar:vertical { background-color: " + p.bgButton + "; }"
            "QScrollBar::handle:vertical { background-color: " + p.textColor + "; }"
            "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical, "
            "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background-color: " + p.bgButton + "; }"
            "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical { background-color: " + p.textColor + "; }"
            "QScrollBar:horizontal { background-color: " + p.bgButton + "; }"
            "QScrollBar::handle:horizontal { background-color: " + p.textColor + "; }";
}

QString BlueSquareFactory::getHeaderStyle() const
{
    return "background-color: #4A7FA8;"
    "border-bottom: 1px solid #1a2533;";
}

QString BlueSquareFactory::getGlobalBackgroundStyle() const
{
    return "QMainWindow { background-color: #1B1212; }";
}

QStackedWidget* BlueSquareFactory::createStackedWidget(QWidget *parent)
{
    return new QStackedWidget(parent);
}

QSpacerItem* BlueSquareFactory::createSpacer(int w, int h,
                                        QSizePolicy::Policy hPolicy,
                                        QSizePolicy::Policy vPolicy)
{
    return new QSpacerItem(w, h, hPolicy, vPolicy);
}
