#include "esimmodel.h"

ESimModel::ESimModel(QObject *parent) : QAbstractTableModel(parent)
{
    checkStateForRow = new bool[3];//021125_TODO
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
            case 1: return tr("Возраст");
            case 2: return tr("Email");
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


int ESimModel::rowCount(const QModelIndex &parent) const//FIXME
{
    if (parent.isValid())
        return 0;//для иерархических моделей
    return persons.size();

}

int ESimModel::columnCount(const QModelIndex &parent) const//FIXME
{
    if (parent.isValid())
        return 0;

    return 3;  // status, name, age//021125
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
bool ESimModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
if (role == Qt::CheckStateRole)
{
    checkStateForRow[index.row()] = value.toInt();
    emit dataChanged(index, index, {role});//021125_???too many arguments 'index'
    return true;
}
return false;
}
//beginInsertRows(QModelIndex(), rowCount(), rowCount());
//persons.append(person);
//endInsertRows();





//Qt::ItemFlags ESimModel::flags(const QModelIndex &index) const
//{
//    return QAbstractListModel::flags(index) | Qt::ItemIsUserCheckable;
//}

Qt::ItemFlags ESimModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;


    if (index.column() == 0) {  // для столбца с чекбоксами
        return QAbstractTableModel::flags(index) |
               Qt::ItemIsUserCheckable |
               Qt::ItemIsEditable;
    }
    return QAbstractTableModel::flags(index);  // для остальных — стандартно
}

QVariant ESimModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::EditRole) {
        return checkStateForRow[index.row()];
    }
    return QVariant();
}











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






bool ESimModel::addPerson(const Person &person)//FIXME
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    persons.append(person);
    endInsertRows();
    return checkStateForRow[0];//021125/должно быть checkStateForRow[rowCount()]
}

bool ESimModel::removePerson(int row)//FIXME
{
    if (row < 0 || row >= rowCount())
        return false;

    beginRemoveRows(QModelIndex(), row, row);
    persons.removeAt(row);
    endRemoveRows();
    return checkStateForRow[row];//021125
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
