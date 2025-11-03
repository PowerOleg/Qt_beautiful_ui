#include "esimmodel.h"

ESimModel::ESimModel(QObject *parent) : QAbstractTableModel(parent)
{
    checkStateForRow = new bool[0];//031125_delete

    items << ItemModel{Qt::Checked, "Item 1", 0};
    items << ItemModel{Qt::Unchecked, "Item 2", 1};
    items << ItemModel{Qt::PartiallyChecked, "Item 3", 2};
}

QVariant ESimModel::headerData(int section, Qt::Orientation orientation, int role) const//FIXME
{
    if (role != Qt::DisplayRole)
           return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0: return tr("Статус");
            case 1: return tr("Имя");
            case 2: return tr("Возраст");
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


int ESimModel::rowCount(const QModelIndex &parent) const//+
{
    if (parent.isValid())
        return 0;//для иерархических моделей
    return items.size();
}

int ESimModel::columnCount(const QModelIndex &parent) const//FIXME
{
    if (parent.isValid())
        return 0;

    return 5;  // id, name, operator_name, status, date
}

bool ESimModel::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

bool ESimModel::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void ESimModel::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}




















// dont't let the default QStyledItemDelegate create the true/false combobox


QVariant ESimModel::data(const QModelIndex &index, int role) const//+
{
//    if (role == Qt::EditRole) {
//        return checkStateForRow[0];//[index.row()];
//    }
    if (!index.isValid())
        return QVariant();
    const ItemModel &item = items[index.row()];

    switch (role)
    {
        case Qt::DisplayRole:
            if (index.column() == 1)
                return item.name;
            break;
        case Qt::CheckStateRole:
            if (index.column() == 0)  // Чекбокс только во втором столбце
                return static_cast<int>(item.checkState);
            break;
    }//031125_TODO_еще case
        return QVariant();
}

bool ESimModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::CheckStateRole || index.column() != 0/*статус на 0 столбце*/)
        return false;

    ItemModel &item = items[index.row()];
    item.checkState = static_cast<Qt::CheckState>(value.toInt());

    emit dataChanged(index, index, {role});
    return true;
}

Qt::ItemFlags ESimModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);
    if (index.column() == 0) {  // 0 столбец — чекбоксы
        return defaultFlags | Qt::ItemIsUserCheckable | Qt::ItemIsEditable;
    }
    return defaultFlags;
}


void ESimModel::setCheckState(int row, Qt::CheckState state)
{
    QModelIndex index = createIndex(row, 0);  // Столбец 0 — чекбоксы
    setData(index, static_cast<int>(state), Qt::CheckStateRole);
}

//bool ESimModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//if (role == Qt::CheckStateRole)
//{
//    checkStateForRow[0] = value.toInt();//[index.row()] = value.toInt();
//    emit dataChanged(index, index, {role});//021125_???too many arguments 'index'
//    return true;
//}
//return false;
//}


//Qt::ItemFlags ESimModel::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return Qt::NoItemFlags;


//    if (index.column() == 0) {  // для столбца с чекбоксами
//        return QAbstractTableModel::flags(index) |
//               Qt::ItemIsUserCheckable |
//               Qt::ItemIsEditable;
//    }
//    return QAbstractTableModel::flags(index);  // для остальных — стандартно
//}













//QVariant ESimModel::data(const QModelIndex &index, int role) const//FIXME
//{
//    if (!index.isValid())
//        return QVariant();

//    if (role == Qt::DisplayRole || role == Qt::EditRole)
//    {
//        const Person &p = persons[index.row()];
//        switch (index.column())
//        {
//            case 0: return p.name;
//            case 1: return p.age;
//            case 2: return p.email;
//        }
//    }
//        return QVariant();
//}

//bool ESimModel::setData(const QModelIndex &index, const QVariant &value, int role)//FIXME//021125_TODO_сделать чтобы чекбокс нажимался
//{
//    if (role == Qt::EditRole)
//    {
//        Person &p = persons[index.row()];
//        switch (index.column())
//        {
//            case 0: p.name = value.toString(); break;
//            case 1: p.age = value.toInt(); break;
//            case 2: p.email = value.toString(); break;
//        }

//        emit dataChanged(index, index, {role});//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!021125_TODO
//        return true;
//    }
//    return false;
//}

//Qt::ItemFlags ESimModel::flags(const QModelIndex &index) const//FIXME//021125_TODO_сделать чтобы чекбокс нажимался
//{
//    if (!index.isValid())
//        return Qt::NoItemFlags;

//    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
//}




















bool ESimModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool ESimModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
    return true;
}

bool ESimModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

bool ESimModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
    return true;
}






bool ESimModel::addItemModel(const ItemModel &itemModel)//FIXME
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(itemModel);
    endInsertRows();
    return checkStateForRow[0];//021125/должно быть checkStateForRow[rowCount()]
}

bool ESimModel::removeItemModel(int row)//FIXME
{
    if (row < 0 || row >= rowCount())
        return checkStateForRow[0];

    beginRemoveRows(QModelIndex(), row, row);
    items.removeAt(row);
    endRemoveRows();
    return checkStateForRow[0];//021125
}


//Qt::ItemFlags ESimModel::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return Qt::NoItemFlags;


//    if (index.column() == 0) {  // для столбца с чекбоксами
//        return QAbstractTableModel::flags(index) |
//               Qt::ItemIsUserCheckable |
//               Qt::ItemIsEditable;
//    }
//    return QAbstractTableModel::flags(index);  // для остальных — стандартно
//}
