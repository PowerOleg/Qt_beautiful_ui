//#include <QDebug>
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QGridLayout>
#include <QMessageBox>
#include <QTableView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindowcontroller.h"
#include "checkboxitemdelegate.h"
#include "esimmodel.h"


void MainWindow::CreateWidgets()
{
    QLayout* centralWidgetLayout = this->centralWidget()->layout();
    if (centralWidgetLayout)
    {
        centralWidgetLayout->setContentsMargins(0, 0, 0, 0);
    }

    QFrame* mainFrame = new QFrame(this);
    mainFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);//mainFrame->setFixedHeight(500);
    mainFrame->setFrameShape(QFrame::NoFrame);
//    mainFrame->setStyleSheet(
//        "border: 2px solid red;"
//        "background-color: gray;"
//    );
    centralWidgetLayout->addWidget(mainFrame);


    QGridLayout* tableViewLayout = new QGridLayout(mainFrame);
    tableViewLayout->setContentsMargins(10, 10, 10, 10);
    mainFrame->setLayout(tableViewLayout);


    QLabel* tableLabel = new QLabel(mainFrame);
    tableLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    tableLabel->setStyleSheet(
            "background-color: #228B22;"
            "color: white;"
            "border: 2px solid #228B22;"
            "border-radius: 6px;"
            "padding: 4px;"
            "font-size: 14px;"
            "font-weight: bold;"
        );

    tableLabel->setText("Список доступных профилей eSIM");
    tableViewLayout->addWidget(tableLabel, 0, 0, 1, 3, Qt::AlignCenter);


    this->currentProfilesTableView = new QTableView(mainFrame);
    currentProfilesTableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    currentProfilesTableView->setFixedHeight(500);
    currentProfilesTableView->setStyleSheet(
                "background-color: #228B22;"
                "color: white;"
                "border: 2px solid #228B22;"
                "padding: 4px;"
                "font-size: 14px;"
                "font-weight: bold;"
            );
    tableViewLayout->addWidget(currentProfilesTableView, 1, 0, 4, 3);
    QFrame* buttonsFrame = new QFrame(mainFrame);
    tableViewLayout->addWidget(buttonsFrame, 4, 4, 1, 1);

    QVBoxLayout* buttonsLayout = new QVBoxLayout(buttonsFrame);
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsFrame->setLayout(buttonsLayout);
    QPushButton* addButton1 = new QPushButton("add");//d
    QPushButton* deleteButton1 = new QPushButton("delete");//d
    buttonsLayout->addWidget(addButton1);
    buttonsLayout->addWidget(deleteButton1);

    QSpacerItem* spacerEnd = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);//d
    tableViewLayout->addItem(spacerEnd, 5, 0);


//    if (!chosen_profile_layout)
//    {
//        QMessageBox::information(this, "Выбор профиля ESim", "Ошибка. Отсутствует стандартное место для вставки выбранного профиля ESim\n");
//    }

  connect(ui->minimizeWindowButton, &QPushButton::clicked, this, &QMainWindow::showMinimized);
  connect(ui->closeWindowButton, &QPushButton::clicked, this, &QMainWindow::close);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    mainWindowController = new MainWindowController();
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
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
        isDragging = true;
        dragStartPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    else
    {
        isDragging = false;
        QMainWindow::mousePressEvent(event);//Передаём событие дальше
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging && (event->buttons() & Qt::LeftButton))
    {
        QPoint new_pos = event->globalPos() - dragStartPosition;//Вычисляем новое положение окна//- frameGeometry().topLeft();
        move(new_pos);
        event->accept();
    }
    else
    {
        QMainWindow::mouseMoveEvent(event);//Передаём событие дальше
    }
}

