#ifndef ESIMMODEL_H
#define ESIMMODEL_H

#define CHECKBOX_COLUMN_NUMBER 3
#define DATE_COLUMN_NUMBER 4

#include <QAbstractTableModel>
#include <QVector>
#include <iostream>
#include <string>
#include <sstream>

class QVariant;

struct ItemModel
{
    quint64 id;
    QString name;
    QString operatorName;
    Qt::CheckState checkState;
    QString date;
    bool isDateInvalid = false;
};

class ESimModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ESimModel(QObject *parent = nullptr);

    using Row = std::vector<QVariant>;
    //для заполнения заголовков таблицы
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    //функционал сортировки по нажатию на заголовок столбца
    void sort(int column, Qt::SortOrder order) override;

    //методы для редактирования модели
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    void addItemModel(const ItemModel &itemModel);
    ItemModel removeItemModel(const int rowNumber);
    void setCheckState(int row, Qt::CheckState state);
    void setDateError(int row, bool isError);
    void insertItemModelAt(int rowNumber, const ItemModel& item);
private:
    QVector<ItemModel> items;//Хранилище данных
};

#endif // ESIMMODEL_H
