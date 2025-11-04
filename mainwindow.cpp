#include <QDebug>
#include <QMouseEvent>
#include <QGridLayout>
#include <QMessageBox>
#include <QTableView>
#include <QVBoxLayout>
#include <QLabel>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindowcontroller.h"
#include "checkboxitemdelegate.h"
#include "esimmodel.h"


void MainWindow::CreateWidgets()
{
    //    mainWindowController = new MainWindowController();
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QLayout* central_widget_layout = this->centralWidget()->layout();
    if (central_widget_layout)
    {
        central_widget_layout->setContentsMargins(0, 0, 0, 0);
    }

    QFrame* main_frame = new QFrame(this);
    main_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    central_widget_layout->addWidget(main_frame);

    QGridLayout* table_view_layout = new QGridLayout(main_frame);
    main_frame->setLayout(table_view_layout);
    this->current_profiles_table_view = new QTableView(main_frame);
    table_view_layout->addWidget(current_profiles_table_view, 0, 0, 4, 3);
    QFrame* buttons_frame = new QFrame(main_frame);
    table_view_layout->addWidget(buttons_frame, 3, 4, 1, 1);

    QVBoxLayout* buttons_layout = new QVBoxLayout(buttons_frame);
    buttons_frame->setLayout(buttons_layout);
    QPushButton* addButton1 = new QPushButton("add");
    QPushButton* deleteButton1 = new QPushButton("delete");
    buttons_layout->addWidget(addButton1);
    buttons_layout->addWidget(deleteButton1);





//    if (!chosen_profile_layout)
//    {
//        QMessageBox::information(this, "Выбор профиля ESim", "Ошибка. Отсутствует стандартное место для вставки выбранного профиля ESim\n");
//    }
//    main_layout->setContentsMargins(0, 0, 0, 0);  // убрать отступы
//    main_layout->addWidget(ui->headerWidget);  // добавляем шапку сверху
//    main_layout->addStretch();





  connect(ui->minimizeWindowButton, &QPushButton::clicked, this, &QMainWindow::showMinimized);
  connect(ui->closeWindowButton, &QPushButton::clicked, this, &QMainWindow::close);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    CreateWidgets();







    //считываем JSON инициализируем профили  засовываем в model и отображаем в TableView
//    ESimModel* model = new ESimModel(this);








//    ui->currentProfilesTableView->setModel(model);
//    CheckBoxItemDelegate* checkbox_delegate = new CheckBoxItemDelegate();
//    ui->currentProfilesTableView->setItemDelegateForColumn(3, checkbox_delegate);













    //    QModelIndex idx = model->index(0, 3);  // строка 0, столбец 3
    //    model->setData(idx, Qt::Checked, Qt::CheckStateRole);  // Вариант 1: напрямую
    //  вспомогательный метод
    //    model->setCheckState(0, Qt::Unchecked);  // Вариант 2: удобнее
    //    QModelIndex idx = model->index(1, 4);
    //    model->setData(idx, "2024-02-15", Qt::EditRole);


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











//    chosenProfile = new Profile(this);
//    mainWindowController->SetChosenProfile(chosenProfile);

}

MainWindow::~MainWindow()
{
    delete ui;
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

