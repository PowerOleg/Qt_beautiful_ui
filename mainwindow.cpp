//#include <QDebug>
#include <QMouseEvent>
#include <QGridLayout>
#include <QMessageBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindowcontroller.h"
#include "checkboxitemdelegate.h"
#include "esimmodel.h"


void MainWindow::Init()
{
    ui->setupUi(this);
    QGridLayout* chosen_profile_layout = ui->chosenGridLayout;
    if (!chosen_profile_layout)
    {
        QMessageBox::information(this, "Выбор профиля ESim", "Ошибка. Отсутствует стандартное место для вставки выбранного профиля ESim\n");
    }
    mainWindowController = new MainWindowController(chosen_profile_layout);
    QLayout* main_layout = this->centralWidget()->layout();
    if (main_layout)
    {
        main_layout->setContentsMargins(0, 0, 0, 0);
    }
    this->setWindowFlags(Qt::FramelessWindowHint);
//    main_layout->setContentsMargins(0, 0, 0, 0);  // убрать отступы
//    main_layout->addWidget(ui->headerWidget);  // добавляем шапку сверху
//    main_layout->addStretch();

    connect(ui->minimizeWindowButton, &QPushButton::clicked, this, &QMainWindow::showMinimized);
    connect(ui->closeWindowButton, &QPushButton::clicked, this, &QMainWindow::close);



    //считываем JSON инициализируем профили  засовываем в model и отображаем в TableView
    ESimModel* model = new ESimModel(this);
//    QModelIndex idx = model->index(0, 3);  // строка 0, столбец 3
//    model->setData(idx, Qt::Checked, Qt::CheckStateRole);  // Вариант 1: напрямую
//  вспомогательный метод
//    model->setCheckState(0, Qt::Unchecked);  // Вариант 2: удобнее


//    QModelIndex idx = model->index(1, 4);
//    model->setData(idx, "2024-02-15", Qt::EditRole);

    ui->currentProfilesTableView->setModel(model);
    CheckBoxItemDelegate* checkbox_delegate = new CheckBoxItemDelegate();
    ui->currentProfilesTableView->setItemDelegateForColumn(3, checkbox_delegate);















    //    const QSqlError err = model->lastError();
    //    if (err.isValid())
    //    {
    //        msg->setText(err.text());
    //        msg->show();
    //    }
    //    else
    //    {
//    // Добавляем tableView в layout вашего окна
//    ui->verticalLayout->addWidget(tableView);
// }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    Init();
//    chosenProfile = new Profile(this);
//    mainWindowController->SetChosenProfile(chosenProfile);

}

MainWindow::~MainWindow()
{
    delete ui;
    mainWindowController->ClearChosenProfile();
    delete mainWindowController;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && ui->headerWidget->geometry().contains(event->pos()))
    {
        is_dragging = true;
        drag_start_position = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    else
    {
        is_dragging = false;
        QMainWindow::mousePressEvent(event);//Передаём событие дальше
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (is_dragging && (event->buttons() & Qt::LeftButton))
    {
        QPoint new_pos = event->globalPos() - drag_start_position;//Вычисляем новое положение окна//- frameGeometry().topLeft();
        move(new_pos);
        event->accept();
    }
    else
    {
        QMainWindow::mouseMoveEvent(event);//Передаём событие дальше
    }
}

