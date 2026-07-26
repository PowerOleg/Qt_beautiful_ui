#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>
#include <QSizePolicy>

class QWidget;
class QLabel;
class QLineEdit;
class QPushButton;
class QDialog;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QTableView;
class QStackedWidget;
class QSpacerItem;
class ESimModel;

class Factory : public QObject
{
    Q_OBJECT
public:
    explicit Factory(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~Factory() {}

    virtual QVBoxLayout* createVBoxLayout(QWidget *parent) = 0;
    virtual QHBoxLayout* createHBoxLayout(QWidget *parent) = 0;
    virtual QGridLayout* createGridLayout(QWidget *parent) = 0;
    virtual QFrame* createFrame(QWidget *parent) = 0;
    virtual QTableView* createTableView() = 0;
    virtual QStackedWidget* createStackedWidget(QWidget *parent) = 0;
    virtual QSpacerItem* createSpacer(int w, int h,
                                       QSizePolicy::Policy hPolicy,
                                       QSizePolicy::Policy vPolicy) = 0;
    virtual QDialog* createDialog(QWidget *parent) = 0;
    virtual QLabel* createLabel(QWidget *parent) = 0;
    virtual QLineEdit* createLineEdit(QWidget *parent) = 0;
    virtual QPushButton* createPushButton(QWidget *parent) = 0;
};

#endif // FACTORY_H
