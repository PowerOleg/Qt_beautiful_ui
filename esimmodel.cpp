#include "esimmodel.h"

ESimModel::ESimModel(QObject *parent) : QAbstractTableModel(parent)
{
    items << ItemModel{0, "Item 1", "Operator", Qt::Checked, ""};
    items << ItemModel{1, "Item 2", "Operator", Qt::Unchecked, ""};
    items << ItemModel{2, "Item 3", "Operator", Qt::PartiallyChecked, ""};
}

QVariant ESimModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
           return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0: return tr("Идентификатор");
            case 1: return tr("Имя");
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
        // FIXME: Implement me!
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

    return 5;  // id, name, operator_name, status, date
}

bool ESimModel::hasChildren(const QModelIndex &parent) const
{
    return items.size() > 0;
}

bool ESimModel::canFetchMore(const QModelIndex &parent) const//Implement me!
{
    // FIXME: Implement me!
    return false;
}

void ESimModel::fetchMore(const QModelIndex &parent)//Implement me!
{
    // FIXME: Implement me!
}

// dont't let the default QStyledItemDelegate create the true/false combobox
QVariant ESimModel::data(const QModelIndex &index, int role) const//031125_TODO_надо переделать под дату
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
                return item.operator_name;
            if (index.column() == 4)
                return item.date;
            break;
        case Qt::CheckStateRole:
            if (index.column() == CHECKBOX_COLUMN_NUM)
                return static_cast<int>(item.checkState);
            break;
    }
        return QVariant();
}

bool ESimModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::CheckStateRole || index.column() != CHECKBOX_COLUMN_NUM)
        return false;

    ItemModel &item = items[index.row()];
    item.checkState = static_cast<Qt::CheckState>(value.toInt());

    emit dataChanged(index, index, {role});
    return true;
}

Qt::ItemFlags ESimModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);
    if (index.column() == CHECKBOX_COLUMN_NUM) {
        return defaultFlags | Qt::ItemIsUserCheckable | Qt::ItemIsEditable;
    }
    return defaultFlags;
}

void ESimModel::setCheckState(int row, Qt::CheckState state)
{
    QModelIndex index = createIndex(row, CHECKBOX_COLUMN_NUM);
    setData(index, static_cast<int>(state), Qt::CheckStateRole);
}


//bool ESimModel::insertRows(int row, int count, const QModelIndex &parent)//Implement me!
//{
//    beginInsertRows(parent, row, row + count - 1);
//    // FIXME: Implement me!    items.append(itemModel);
//    endInsertRows();
//    return true;
//}

//bool ESimModel::insertColumns(int column, int count, const QModelIndex &parent)//Implement me!
//{
//    beginInsertColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    endInsertColumns();
//    return true;
//}

//bool ESimModel::removeRows(int row, int count, const QModelIndex &parent)//Implement me!
//{
//    beginRemoveRows(parent, row, row + count - 1);
//    // FIXME: Implement me!
//    endRemoveRows();
//    return true;
//}

//bool ESimModel::removeColumns(int column, int count, const QModelIndex &parent)//Implement me!
//{
//    beginRemoveColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    endRemoveColumns();
//    return true;
//}


//void ESimModel::addItemModel(const ItemModel &itemModel)
//{
//    beginInsertRows(QModelIndex(), rowCount(), rowCount());
//    items.append(itemModel);
//    endInsertRows();
//}

//void ESimModel::removeItemModel(int row)//FIXME
//{
//    if (row < 0 || row >= rowCount())
//        return;

//    beginRemoveRows(QModelIndex(), row, row);
//    items.removeAt(row);
//    endRemoveRows();
//}
