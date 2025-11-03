//#include <QDebug>
#include <QMouseEvent>
#include <QGridLayout>
#include <QMessageBox>
#include <QTableView>
#include <QVBoxLayout>


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindowcontroller.h"
#include "checkboxitemdelegate.h"
#include "esimmodel.h"


void MainWindow::CreateWidgets()
{
    ui->setupUi(this);
        ui->editFrame->setVisible(false);
    mainWindowController = new MainWindowController();
    QLayout* main_layout = this->centralWidget()->layout();
    if (main_layout)
    {
        main_layout->setContentsMargins(0, 0, 0, 0);
    }
    this->setWindowFlags(Qt::FramelessWindowHint);

    QFrame* table_view_frame = new QFrame(this);
    main_layout->addWidget(table_view_frame);
    QGridLayout* chosen_profile_layout1 = new QGridLayout(this);
    table_view_frame->setLayout(chosen_profile_layout1);




    this->current_profiles_table_view1 = new QTableView(this);//QTableView* current_profiles_table_view = ui->currentProfilesTableView;
    chosen_profile_layout1->addWidget(current_profiles_table_view1, 0, 0, 4, 3);



    QFrame* buttons_frame = new QFrame(this);
    chosen_profile_layout1->addWidget(buttons_frame, 2, 4, 2, 1);



    QVBoxLayout* buttons_layout = new QVBoxLayout;
    QPushButton* addButton1 = new QPushButton("add");
    QPushButton* deleteButton1 = new QPushButton("delete");
    buttons_layout->addWidget(addButton1);
    buttons_layout->addWidget(deleteButton1);
    buttons_frame->setLayout(buttons_layout);


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
//    mainWindowController->ClearChosenProfile();//031125
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

