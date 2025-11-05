#include <QTableView>
#include <QHeaderView>
#include "tablecontroller.h"
#include "esimmodel.h"
#include "checkboxitemdelegate.h"

TableController::TableController(QObject* parent, QTableView* tableView) : QObject(parent), currentProfilesTableView(tableView)
{
    currentProfilesTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    currentProfilesTableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    currentProfilesTableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    currentProfilesTableView->setFixedHeight(500);
    currentProfilesTableView->verticalHeader()->hide();
    currentProfilesTableView->horizontalHeader()->setMinimumSectionSize(50);

    this->tableModel = new ESimModel(parent);
    currentProfilesTableView->setModel(tableModel);
    this->checkboxDelegate = new CheckBoxItemDelegate();
    currentProfilesTableView->setItemDelegateForColumn(tableModel->CHECKBOX_COLUMN_NUM, checkboxDelegate);

    //для таблицы currentProfilesTableView ширину ячеек делаем автоизменяемыми по контенту
    currentProfilesTableView->resizeColumnsToContents();
    connect(this->tableModel, &QAbstractItemModel::dataChanged, this->currentProfilesTableView, &QTableView::resizeColumnsToContents);
    connect(this->tableModel, &QAbstractItemModel::rowsInserted, this->currentProfilesTableView, &QTableView::resizeColumnsToContents);
}

TableController::~TableController()
{
//    delete tableModel;
    delete checkboxDelegate;
}

void TableController::AddProfile(QString name, QString nameOperator)
{
    ItemModel itemModel{rowId++, name, nameOperator, Qt::Unchecked, ""};
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










//void MainWindowController::ClearChosenProfile()
//{
//    while (chosen_profile_layout->count() > 0)
//    {
//        QLayoutItem* item = chosen_profile_layout->takeAt(0);
//        if (item->widget())
//        {
//            delete item->widget();//удаляем виджет
//        }
//        delete item;//удаляем QLayoutItem
//    }
//}
