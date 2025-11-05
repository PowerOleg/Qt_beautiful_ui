#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class TableController;
class ESimModel;
class AddProfile;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    TableController* tableController = nullptr;
//    QTableView* currentProfilesTableView = nullptr;
    QPushButton* addButton = nullptr;
    QPushButton* deleteButton = nullptr;
    QPushButton* refreshButton = nullptr;
    QDialog* addDialog = nullptr;
    bool isDragging;//Флаг:идёт ли перетаскивание
    QPoint dragStartPosition;//Начальная точка нажатия перетаскивания окна

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private slots:
     void AddButtonClicked();

private:
     void CreateWidgets();
     void InitActions();
};
#endif // MAINWINDOW_H
