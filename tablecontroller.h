#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>

class QWidget;
class QGridLayout;
class QTableView;
class ESimModel;
class CheckBoxItemDelegate;

class TableController : public QObject
{
    Q_OBJECT
public:
    explicit TableController(QObject* parent = nullptr, QTableView* tableView = nullptr);
    ~TableController();

private:
    QTableView* currentProfilesTableView = nullptr;
    ESimModel* tableModel = nullptr;
    CheckBoxItemDelegate* checkboxDelegate = nullptr;
};

#endif // MAINWINDOWCONTROLLER_H
