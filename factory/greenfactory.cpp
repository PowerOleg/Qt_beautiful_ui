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
    d->setStyleSheet(
        "background-color: #228B22;"
        "color: white;"
        "font-size: 14px;"
        "font-weight: bold;"
    );
    return d;
}

QLabel* GreenFactory::createLabel(QWidget *parent)
{
    QLabel* l = new QLabel(parent);
    l->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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
    );
    le->setFixedWidth(200);
    return le;
}

QPushButton* GreenFactory::createPushButton(QWidget *parent)
{
    QPushButton* b = new QPushButton(parent);
//    b->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//    b->setStyleSheet("background-color: #1B1212;"
//        "border-radius: 10px;");
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
    return new QTableView();
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
