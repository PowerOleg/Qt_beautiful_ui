#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>

class QGridLayout;
class QTableView;
class ESimModel;
class CheckBoxItemDelegate;

const int TABLE_WIDTH = 600;//глобальный параметр для задания ширины таблицы в диалоговом окне
const int TABLE_HEIGHT = 600;//глобальный параметр для задания высоты таблицы в диалоговом окне

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

    quint64 idGlobal = 0;//параметр для реализации сквозного уникального инкрементирующего идентификатора для всей таблицы
public slots:
    void RemoveSelectedProfile();
    void RefreshTable();
};

#endif // MAINWINDOWCONTROLLER_H
