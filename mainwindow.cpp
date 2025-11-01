#include <QDebug>
#include <QMouseEvent>
#include <QGridLayout>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::init()
{
    ui->setupUi(this);
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
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    init();
//    QGridLayout* grid = this->findChild<QGridLayout*>("chosenGridLayout");
//    QGridLayout* chosen_product_layout = ui->chosenGridLayout;//->layout();//chosenGridLayout//chosenProductFrame
    QLayout* grid = ui->chosenProductFrame->layout();

    if (grid)
    {
        qDebug() << "grid";
//        grid->setAlignment(Qt::AlignLeft);
        QFrame* my_frame = new QFrame(this);
        my_frame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        my_frame->setFixedHeight(50);
             my_frame->setFixedWidth(150);
        Profile* new_profile = new Profile(this);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!300 раз подумай , я же буду постоянно удалять объект
        new_profile->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        new_profile->setFixedHeight(50);
        new_profile->setFixedWidth(150);
       // Profile profile;
//        grid->addWidget(new_profile, 0, 0, Qt::AlignLeft);
//        grid->addWidget(my_frame, 0, 1, Qt::AlignLeft);


        grid->addWidget(my_frame);
        grid->addWidget(new_profile);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
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

