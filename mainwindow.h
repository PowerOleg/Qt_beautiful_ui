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
class QLineEdit;
class QGridLayout;
class QStackedWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    TableController* tableController = nullptr;
    QPushButton* addButton = nullptr;
    QPushButton* deleteButton = nullptr;
    QPushButton* refreshButton = nullptr;
    QDialog* addDialog = nullptr;
    QLineEdit* nameText = nullptr;
    QLineEdit* nameOperatorText = nullptr;
    bool isDragging;//Флаг:идёт ли перетаскивание
    QPoint dragStartPosition;//Начальная точка нажатия перетаскивания окна

    QStackedWidget* tableStacked;
    QGridLayout* tableViewLayout = nullptr;
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private slots:
    void OnAddButtonClicked();
    void OnOkButtonDialogClicked();
private:
     void CreateWidgets();
     void InitActions();
     void InitAddButtonDialog();
};
#endif // MAINWINDOW_H
