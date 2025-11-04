//#include <QMessageBox>
#include <QTableView>
#include <QHeaderView>
//#include <QAbstractItemModel>
#include "tablecontroller.h"
#include "esimmodel.h"
#include "checkboxitemdelegate.h"

TableController::TableController(QObject* parent, QTableView* tableView) : QObject(parent), currentProfilesTableView(tableView)
{
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








//bool MainWindowController::SetChosenProfile(Profile* profile)
//{
//    if (profile)
//    {
//        profile->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//        profile->setFixedHeight(200);
//        profile->setFixedWidth(300);
//        chosen_profile_layout->addWidget(profile, 0, 0, Qt::AlignLeft);
//        return true;
//    }
//    return false;
//}

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
