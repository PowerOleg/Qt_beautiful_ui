#ifndef ESIMMODEL_H
#define ESIMMODEL_H

#include <QAbstractTableModel>
#include <QVector>

class QVariant;

struct ItemModel
{
    quint64 id;
    QString name;
    QString operatorName;
    Qt::CheckState checkState;
    QString date;
};

class ESimModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ESimModel(QObject *parent = nullptr);
    const int checkboxColumnNumber = 3;
    const int dateColumnNumber = 4;

    using Row = std::vector<QVariant>;
    //для заполнения заголовков таблицы
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    void sort(int column, Qt::SortOrder order) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    //методы для редактирования модели
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    void addItemModel(const ItemModel &itemModel);
    void removeItemModel(const int row);
    void setCheckState(int row, Qt::CheckState state);//Метод для установки чекбокса
private:
    QVector<ItemModel> items;//Хранилище данных
};

#endif // ESIMMODEL_H
