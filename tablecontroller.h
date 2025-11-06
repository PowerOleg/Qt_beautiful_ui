#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>

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

    void AddProfile(QString name, QString nameOperator);
    bool ReadFile(const QString& filename);
private:
    QTableView* currentProfilesTableView = nullptr;
    ESimModel* tableModel = nullptr;
    CheckBoxItemDelegate* checkboxDelegate = nullptr;

    quint64 idGlobal = 0;
public slots:
    void RemoveSelectedProfile();
};

#endif // MAINWINDOWCONTROLLER_H
