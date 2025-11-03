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
//    QStandardItemModel* model = new QStandardItemModel(3, 1);
    ESimModel* model = new ESimModel(this);
//    model->addPerson({true, "Иван", 25});
//    model->addPerson({false, "Мария", 30});
//    model->setData(1, 0, new QStandardItem("Элемент 2"));

    QModelIndex idx = model->index(0, 0);  // строка 0, столбец 1
    model->setData(idx, Qt::Checked, Qt::CheckStateRole);  // Вариант 1: напрямую
//  вспомогательный метод
//    model->setCheckState(0, Qt::Unchecked);  // Вариант 2: удобнее

    // Настраиваем tableView
    ui->currentProfilesTableView->setModel(model);


    // Устанавливаем делегат для первого столбца
    CheckBoxItemDelegate* checkbox_delegate = new CheckBoxItemDelegate();//(ui->currentProfilesTableView);
    ui->currentProfilesTableView->setItemDelegateForColumn(0, checkbox_delegate);



//-----------------------------------------------------------------------
//    m_p_QTableView->setItemDelegateForColumn(iTableColumnIndex, new GFQtCheckboxItemDelegate() );
//    ...
//    bool yesno ...;
//    pGrid->setData(index, yesno, Qt::CheckStateRole);



//    Person person{"Иван", 25, "ivan@example.com"};
//    QStandardItem* item1 = new QStandardItem("Элемент 1");
//    model->addPerson(item1);


















//    Попытка2
//    // Создаём модель и заполняем данными
//    ESimModel* model = new ESimModel(this);
//    model->addPerson({"Иван", 25, "ivan@example.com"});
//    model->addPerson({"Мария", 30, "maria@example.com"});
//    ui->currentProfilesTableView->setModel(model);



//    // Связываем с представлением
////    QTableView *tableView = new QTableView(this);
////    tableView->setModel(model);

//    // Добавляем tableView в layout вашего окна
////    ui->verticalLayout->addWidget(tableView);











//Попытка1
//    const QSqlError err = model->lastError();
//    if (err.isValid())
//    {
//        msg->setText(err.text());
//        msg->show();
//    }
//    else
//    {
//        ui->tv_result->setModel(model);
//        if (ui->cb_category->currentIndex() == 0)
//        {
//            ui->tv_result->hideColumn(0);
//        } else
//        {
//             ui->tv_result->showColumn(0);
//        }
//    }


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

