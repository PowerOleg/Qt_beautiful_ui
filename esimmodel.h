#ifndef ESIMMODEL_H
#define ESIMMODEL_H

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

//    friend std::ostream& operator<<(std::ostream& os, const ItemModel& item);
};

/*QDebug operator<<(QDebug dbg, const ItemModel& person)
{
    QDebugStateSaver saver(dbg);  // Сохраняет состояние потока
    dbg.nospace() << "Person(name: "
                 << person.name << ", age: "
                 << person.id << ", occupation: "
                 << person.date << ")";
    return dbg.maybeSpace();  // Восстанавливает пробелы
}*/

//std::ostream& operator<<(std::ostream& os, const ItemModel& item) {
//    os << "Имя: " << item.name.toStdString()/*.toUtf8().constData()*/ << "";
//    return os;
//}

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
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    //функциональность сортировки по нажатию на заголовок столбца
    void sort(int column, Qt::SortOrder order) override;

    //методы для редактирования модели
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    void addItemModel(const ItemModel &itemModel);
    void removeItemModel(const int row);
    void setCheckState(int row, Qt::CheckState state);//Метод для установки чекбокса
private:
    QVector<ItemModel> items;//Хранилище данных
};

#endif // ESIMMODEL_H
