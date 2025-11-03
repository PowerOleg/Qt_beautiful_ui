#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "profile.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindowController;
class ESimModel;
class QTableView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    MainWindowController* mainWindowController = nullptr;
    QTableView* current_profiles_table_view1 = nullptr;

    bool is_dragging;//Флаг:идёт ли перетаскивание
    QPoint drag_start_position;//Начальная точка нажатия перетаскивания окна

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
private:
     void CreateWidgets();
};
#endif // MAINWINDOW_H
