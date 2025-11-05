#ifndef ESIMMODEL_H
#define ESIMMODEL_H

#include <QAbstractTableModel>
#include <QVector>

struct ItemModel
{
    quint64 id;
    QString name;
    QString operator_name;
    Qt::CheckState checkState;
    QString date;
};

class ESimModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ESimModel(QObject *parent = nullptr);
    const int CHECKBOX_COLUMN_NUM = 3;
    const int DATE_COLUMN_NUM = 4;

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // Fetch data dynamically:
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

//    // Add data:
//    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
//    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
//    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
//    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;


    //custom data managing
    void addItemModel(const ItemModel* itemModel);
    void removeItemModel(const int row);

    void setCheckState(int row, Qt::CheckState state);//Метод для установки чекбокса
private:
    QVector<ItemModel> items;//Хранилище данных
};

#endif // ESIMMODEL_H
