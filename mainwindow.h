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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
//    void MousePressEvent(QMouseEvent *event);
//    void MouseMoveEvent(QMouseEvent *event);
    Ui::MainWindow *ui;
    //SLOTS: showMinimized(), showMaximized()/showNormal(), close()
    /*перетаскивать: переопределите mousePressEvent и mouseMoveEvent для вашей «шапки»;

сворачивать/разворачивать/закрывать: добавьте кнопки и подключите слоты к showMinimized(), showMaximized()/showNormal(), close().*/
};
#endif // MAINWINDOW_H
