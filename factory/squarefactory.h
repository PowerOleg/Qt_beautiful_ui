#ifndef SQUAREFACTORY_H
#define SQUAREFACTORY_H

#include "factory.h"

class SquareFactory : public Factory
{
    Q_OBJECT
public:
    explicit SquareFactory(QObject *parent = nullptr);
    QVBoxLayout* createVBoxLayout(QWidget *parent) override;
    QHBoxLayout* createHBoxLayout(QWidget *parent) override;
    QGridLayout* createGridLayout(QWidget *parent) override;
    QFrame* createFrame(QWidget *parent) override;
    QTableView* createTableView() override;
    QStackedWidget* createStackedWidget(QWidget *parent) override;
    QSpacerItem* createSpacer(int w, int h,
                              QSizePolicy::Policy hPolicy,
                              QSizePolicy::Policy vPolicy) override;
    QDialog* createDialog(QWidget *parent) override;
    QLabel* createLabel(QWidget *parent) override;
    QLineEdit* createLineEdit(QWidget *parent) override;
    QPushButton* createPushButton(QWidget *parent) override;
    QString getTableViewStyle() const override;
    QString getGlobalBackgroundStyle() const override;
    QString getHeaderStyle() const override;
};

#endif // SQUAREFACTORY_H
