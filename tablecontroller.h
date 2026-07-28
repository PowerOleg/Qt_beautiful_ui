#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>
#include <QAbstractItemModel>
#include "esimmodel.h"
#include <iostream>
#include <string>
#include <sstream>
#include "./command/icommand.h"

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

    ItemModel addProfile(QString name, QString nameOperator);
    bool readFile(const QString& filename);
    void undo();
    void redo();
    bool canUndo() const;
    bool canRedo() const;
private:
    QTableView* currentProfilesTableView = nullptr;
    ESimModel* tableModel = nullptr;
    CheckBoxItemDelegate* checkboxDelegate = nullptr;
    quint64 idGlobal = 0;//параметр для реализации сквозного уникального инкрементирующего идентификатора для всей таблицы

    bool isWrongDate(const QString& text) const;

    QVector<ICommand*> undoStack;
    QVector<ICommand*> redoStack;
public slots:
    void removeSelectedProfile();
    void checkTable();
};

#endif // MAINWINDOWCONTROLLER_H
