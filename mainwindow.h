#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "profile.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindowController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    MainWindowController* mainWindowController = nullptr;
    bool is_dragging;//Флаг:идёт ли перетаскивание
    QPoint drag_start_position;//Начальная точка нажатия перетаскивания окна
    Profile* chosenProfile = nullptr;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
private:
     void Init();
};
#endif // MAINWINDOW_H
