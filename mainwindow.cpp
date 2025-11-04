//#include <QDebug>
#include <QMouseEvent>
#include <QGridLayout>
#include <QMessageBox>
#include <QTableView>
#include <QHeaderView>
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
    currentProfilesTableView->verticalHeader()->hide();

    tableViewLayout->addWidget(currentProfilesTableView, 1, 0, 4, 3);
    //    if (нечем изначально наполнить currentProfilesTableView)
    //    {
    //        QMessageBox::information(this, "Выбор профиля ESim", "Ошибка. Отсутствует стандартное место для вставки выбранного профиля ESim\n");
    //    }

    QFrame* buttonsFrame = new QFrame(mainFrame);
    tableViewLayout->addWidget(buttonsFrame, 4, 4, 1, 1);

    QVBoxLayout* buttonsLayout = new QVBoxLayout(buttonsFrame);
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsFrame->setLayout(buttonsLayout);
    QPushButton* addButton = new QPushButton("Добавить профиль", buttonsFrame);
    QPushButton* deleteButton = new QPushButton("Удалить выбранный профиль", buttonsFrame);
    QPushButton* refreshButton = new QPushButton("Обновить список", buttonsFrame);
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(deleteButton);
    buttonsLayout->addWidget(refreshButton);

    QSpacerItem* spacerEnd = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    tableViewLayout->addItem(spacerEnd, 5, 0);

}

void MainWindow::InitActions()
{
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
    ESimModel* tableModel = new ESimModel(this);
    currentProfilesTableView->setModel(tableModel);
    CheckBoxItemDelegate* checkbox_delegate = new CheckBoxItemDelegate();
    currentProfilesTableView->setItemDelegateForColumn(tableModel->CHECKBOX_COLUMN_NUM, checkbox_delegate);

    //для таблицы currentProfilesTableView ширину ячеек делаем автоизменяемыми по контенту
    currentProfilesTableView->resizeColumnsToContents();
    connect(tableModel, &QAbstractItemModel::dataChanged, currentProfilesTableView, &QTableView::resizeColumnsToContents);
    connect(tableModel, &QAbstractItemModel::rowsInserted, currentProfilesTableView, &QTableView::resizeColumnsToContents);
    InitActions();



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
        QPoint new_pos = event->globalPos() - dragStartPosition;
        move(new_pos);
        event->accept();
    }
    else
    {
        QMainWindow::mouseMoveEvent(event);//Передаём событие дальше
    }
}

