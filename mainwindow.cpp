//#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLayout* main_layout = this->centralWidget()->layout();
    if (main_layout)
    {
        main_layout->setContentsMargins(0, 0, 0, 0);
    }
    this->setWindowFlags(Qt::FramelessWindowHint);
//    ui->headerWidget->setGeometry(QRect(0, 0, 100, 30));
//    QVBoxLayout* main_layout = new QVBoxLayout(centralWidget());  // centralWidget() — главный виджет окна
//    main_layout->setContentsMargins(0, 0, 0, 0);  // убрать отступы
//    main_layout->addWidget(ui->headerWidget);  // добавляем шапку сверху
//    main_layout->addStretch();



    connect(ui->minimizeWindowButton, &QPushButton::clicked, this, &QMainWindow::showMinimized);
    connect(ui->closeWindowButton, &QPushButton::clicked, this, &QMainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::MousePressEvent(QMouseEvent *event) {
//    if (event->button() == Qt::LeftButton &&
//        ui->headerWidget->geometry().contains(event->pos())) {
//        dragPosition = event->globalPos() - frameGeometry().topLeft();
//        event->accept();
//    }
//}

//void MainWindow::MouseMoveEvent(QMouseEvent *event) {
//    if (event->buttons() & Qt::LeftButton) {
//        move(event->globalPos() - dragPosition);
//        event->accept();
//    }
//}

