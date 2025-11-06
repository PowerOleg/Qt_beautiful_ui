#include "esimmodel.h"
#include "QDate"
#include <algorithm>

ESimModel::ESimModel(QObject *parent) : QAbstractTableModel(parent)
{}

QVariant ESimModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
           return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0: return tr("ID");
            case 1: return tr("Название");
            case 2: return tr("Оператор");
            case 3: return tr("Статус");
            case 4: return tr("Дата активации");
        }
    }
    return QVariant();
}

bool ESimModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role))
    {
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}


int ESimModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;//для иерархических моделей
    return items.size();
}

int ESimModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 5;//id, name, operator_name, status, date
}

bool ESimModel::hasChildren(const QModelIndex &parent) const
{
    return items.size() > 0;
}

QVariant ESimModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    const ItemModel &item = items[index.row()];

    switch (role)
    {
        case Qt::DisplayRole:
            if (index.column() == 0)
                return item.id;
            if (index.column() == 1)
                return item.name;
            if (index.column() == 2)
                return item.operatorName;
            if (index.column() == dateColumnNumber)
                return item.date;
            break;
        case Qt::CheckStateRole:
            if (index.column() == checkboxColumnNumber)
                return static_cast<int>(item.checkState);
            break;
    }
        return QVariant();
}

bool ESimModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    ItemModel &item = items[index.row()];

    if (role == Qt::CheckStateRole && index.column() == checkboxColumnNumber)
    {
        item.checkState = static_cast<Qt::CheckState>(value.toInt());
        emit dataChanged(index, index, {role});
        QString date_value = QDate::currentDate().toString("yyyy-MM-dd");
        if (!value.toBool())
        {
            date_value = "";
        }

        QModelIndex date_idx = index.model()->index(index.row(), dateColumnNumber);
        setData(date_idx, date_value, Qt::EditRole);
        return true;
    }

    //для изменения даты
    if (role == Qt::EditRole)
    {
        item.date = value.toString();
        emit dataChanged(index, index, {role});
        return true;
    }

    return false;
}

Qt::ItemFlags ESimModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);

    if (index.column() == checkboxColumnNumber)//Чекбокс
        return defaultFlags | Qt::ItemIsUserCheckable | Qt::ItemIsEditable;

//    if (index.column() == DATE_COLUMN_NUM)//Дата
//        return defaultFlags | Qt::ItemIsEditable;//Разрешаем редактирование

    return defaultFlags;
}

void ESimModel::setCheckState(int row, Qt::CheckState state)
{
    QModelIndex index = createIndex(row, checkboxColumnNumber);
    setData(index, static_cast<int>(state), Qt::CheckStateRole);
}


void ESimModel::addItemModel(const ItemModel &itemModel)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(itemModel);
    endInsertRows();
}

void ESimModel::removeItemModel(const int rowNumber)
{
    if (rowNumber < 0 || rowNumber >= rowCount())
        return;

    beginRemoveRows(QModelIndex(), rowNumber, rowNumber);
    items.removeAt(rowNumber);
    endRemoveRows();
}

void ESimModel::sort(int column, Qt::SortOrder order)
{
    if (column < 0 || column >= columnCount())
        return;

    beginResetModel();//Уведомляем представления о начале изменения модели
    std::sort(items.begin(), items.end(), [column, order](const ItemModel& a, const ItemModel& b)
    {
        if (column == 0)
        {
            const quint64 aNum = a.id;
            const quint64 bNum = b.id;
            return (order == Qt::AscendingOrder) ? aNum < bNum : aNum > bNum;
        }
        if (column == 1)
        {
            const QString aName = a.name;
            const QString bName = b.name;
            return (order == Qt::AscendingOrder) ? aName < bName : aName > bName;
        }
        if (column == 2)
        {
            const QString aName = a.operatorName;
            const QString bName = b.operatorName;
            return (order == Qt::AscendingOrder) ? aName < bName : aName > bName;
        }
        if (column == 4)
        {
            const QString aDate = a.date;
            const QString bDate = b.date;
            return (order == Qt::AscendingOrder) ? aDate < bDate : aDate > bDate;
        }
        if (column == 3)
        {
            const Qt::CheckState aNum = a.checkState;
            const Qt::CheckState bNum = b.checkState;
            return (order == Qt::AscendingOrder) ? aNum < bNum : aNum > bNum;
        }
        return false;
    });
    endResetModel();//Конец изменения модели
}
