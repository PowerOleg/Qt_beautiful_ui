#include "esimmodel.h"
#include "QDate"

ESimModel::ESimModel(QObject *parent) : QAbstractTableModel(parent)
{
    items << ItemModel{0, "Operator A eSIM", "Vodafone", Qt::Checked, "2023-10-05"};
    items << ItemModel{1, "Operator B eSIM", "Kolyaphone", Qt::Unchecked, ""};
    items << ItemModel{2, "Operator C eSIM", "Company 3", Qt::PartiallyChecked, ""};
}

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
            if (index.column() == DATE_COLUMN_NUM)
                return item.date;
            break;
        case Qt::CheckStateRole:
            if (index.column() == CHECKBOX_COLUMN_NUM)
                return static_cast<int>(item.check_state);
            break;
    }
        return QVariant();
}

bool ESimModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    ItemModel &item = items[index.row()];

    if (role == Qt::CheckStateRole && index.column() == CHECKBOX_COLUMN_NUM)
    {
        item.check_state = static_cast<Qt::CheckState>(value.toInt());
        emit dataChanged(index, index, {role});
        QString date_value = QDate::currentDate().toString("yyyy-MM-dd");
        if (!value.toBool())
        {
            date_value = "";
        }

        QModelIndex date_idx = index.model()->index(index.row(), DATE_COLUMN_NUM);
        setData(date_idx, date_value, Qt::EditRole);
        return true;
    }

    //для изменения даты
    if (role == Qt::EditRole)//&& index.column() == DATE_COLUMN_NUM
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

    if (index.column() == CHECKBOX_COLUMN_NUM)//Чекбокс
        return defaultFlags | Qt::ItemIsUserCheckable | Qt::ItemIsEditable;

//    if (index.column() == DATE_COLUMN_NUM)//Дата
//        return defaultFlags | Qt::ItemIsEditable;//Разрешаем редактирование

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
