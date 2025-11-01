#include "esimmodel.h"

ESimModel::ESimModel(QObject *parent) : QAbstractTableModel(parent)
{
}

QVariant ESimModel::headerData(int section, Qt::Orientation orientation, int role) const//FIXME
{
    if (role != Qt::DisplayRole)
           return QVariant();

    if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0: return tr("Имя");
            case 1: return tr("Возраст");
            case 2: return tr("Email");
            }
        }
        return QVariant();
}

bool ESimModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
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

    return 3;  // name, age, email
}

bool ESimModel::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
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

QVariant ESimModel::data(const QModelIndex &index, int role) const//FIXME
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        const Person &p = persons[index.row()];
        switch (index.column())
        {
            case 0: return p.name;
            case 1: return p.age;
            case 2: return p.email;
        }
    }
        return QVariant();
}

bool ESimModel::setData(const QModelIndex &index, const QVariant &value, int role)//FIXME
{
    if (role == Qt::EditRole)
    {
        Person &p = persons[index.row()];
        switch (index.column())
        {
            case 0: p.name = value.toString(); break;
            case 1: p.age = value.toInt(); break;
            case 2: p.email = value.toString(); break;
        }
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;

//    if (data(index, role) != value) {
//        // FIXME: Implement me!
//        emit dataChanged(index, index, {role});
//        return true;
//    }
//    return false;
}

Qt::ItemFlags ESimModel::flags(const QModelIndex &index) const//FIXME
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;

//    if (!index.isValid())
//        return Qt::NoItemFlags;

//    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

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






void ESimModel::addPerson(const Person &person)//FIXME
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    persons.append(person);
    endInsertRows();
}

void ESimModel::removePerson(int row)//FIXME
{
    if (row < 0 || row >= rowCount())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    persons.removeAt(row);
    endRemoveRows();
}
