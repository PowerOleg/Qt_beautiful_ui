#include <QTableView>
#include <QHeaderView>
#include "tablecontroller.h"
#include "esimmodel.h"
#include "checkboxitemdelegate.h"

#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFileInfo>
#include <QString>

TableController::TableController(QObject* parent, QTableView* tableView) : QObject(parent), currentProfilesTableView(tableView)
{
    //задаем визуальные параметры для таблицы
    currentProfilesTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    currentProfilesTableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    currentProfilesTableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    currentProfilesTableView->setMinimumSize(TABLE_WIDTH, TABLE_HEIGHT);
    currentProfilesTableView->verticalHeader()->hide();
    currentProfilesTableView->horizontalHeader()->setMinimumSectionSize(50);

    //создаем модель таблицы и задаем параметры для модели
    this->tableModel = new ESimModel(parent);
    currentProfilesTableView->setModel(tableModel);

    //функционал чтобы чекбокс нажимался
    this->checkboxDelegate = new CheckBoxItemDelegate();
    currentProfilesTableView->setItemDelegateForColumn(tableModel->checkboxColumnNumber, checkboxDelegate);

    //для таблицы currentProfilesTableView ширину ячеек делаем автоизменяемыми по контенту
    currentProfilesTableView->resizeColumnsToContents();
    connect(this->tableModel, &QAbstractItemModel::dataChanged, this->currentProfilesTableView, &QTableView::resizeColumnsToContents);
    connect(this->tableModel, &QAbstractItemModel::rowsInserted, this->currentProfilesTableView, &QTableView::resizeColumnsToContents);

    //функциональность сортировки по нажатию на заголовок столбца
    currentProfilesTableView->setSortingEnabled(true);
}

TableController::~TableController()
{
    delete currentProfilesTableView;
    delete checkboxDelegate;
}

void TableController::AddProfile(QString name, QString nameOperator)
{
    ItemModel itemModel{idGlobal++, name, nameOperator, Qt::Unchecked, ""};
    tableModel->addItemModel(itemModel);
    currentProfilesTableView->selectionModel()->clearSelection();
}

void TableController::RemoveSelectedProfile()
{
    QItemSelectionModel* selectionModel = currentProfilesTableView->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
    if (selectedIndexes.isEmpty())
        return;
    const QModelIndex modelIndex = selectedIndexes.at(0);
    tableModel->removeItemModel(modelIndex.row());
    currentProfilesTableView->selectionModel()->clearSelection();
}

/**
 * @brief Метод возвращает true только если файл читается и не пустой
 * @param filename
 *
 */
bool TableController::ReadFile(const QString& filename)
{
    if (filename == "")
    {
        const QString message = QString("Отсутствует файл с профилями eSIM");
        QMessageBox::information(nullptr, "Ошибка", message);
        return false;
    }
    QFileInfo fileInfo(filename);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        const QString message = QString("Невозможно открыть файл %1").arg(fileInfo.fileName());
        QMessageBox::information(nullptr, "Ошибка", message);
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    if (data.size() < 20)
    {
        return false;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError)
    {
        const QString message = QString("Ошибка обработки данных файла %1: %2").arg(fileInfo.fileName()).arg(error.errorString());
        QMessageBox::information(nullptr, "Ошибка", message);
        return false;
    }

    quint64 idMax = 0;
    QJsonArray itemModelArray = doc.array();
    for (const QJsonValue& value : itemModelArray)
    {
        QJsonObject obj = value.toObject();
        ItemModel item;
        quint64 id = obj["id"].toVariant().toULongLong();
        idMax = idMax < id ? id : idMax;
        item.id = id;
        item.name = obj["name"].toString();
        item.operatorName = obj["operatorName"].toString();
        item.checkState = static_cast<Qt::CheckState>(obj["checkState"].toInt());
        item.date = obj["date"].toString();

        tableModel->addItemModel(item);
    }
    idGlobal = ++idMax;
    return true;
}

void TableController::RefreshTable()
{
    int rowMax = tableModel->rowCount();
    if (rowMax == 0)
        return;

    emit tableModel->dataChanged(tableModel->index(0, 0), tableModel->index(rowMax - 1, tableModel->dateColumnNumber));
    currentProfilesTableView->selectionModel()->clearSelection();
}
