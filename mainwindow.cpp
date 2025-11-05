//#include <QDebug>
#include <QDialog>
#include <QMouseEvent>
#include <QGridLayout>
#include <QMessageBox>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpacerItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tablecontroller.h"

void MainWindow::InitAddButtonDialog()
{
    this->addDialog = new QDialog(this);
    addDialog->setWindowTitle("Добавить профиль");
    addDialog->resize(300, 200);
    addDialog->setStyleSheet(
            "background-color: #228B22;"
            "color: white;"
            "font-size: 14px;"
            "font-weight: bold;"
        );
    QVBoxLayout* dialogLayout = new QVBoxLayout(addDialog);
    dialogLayout->setContentsMargins(20, 20, 20, 20);
    dialogLayout->setSpacing(10);


    QLabel* nameLabel = new QLabel(addDialog);
    nameLabel->setText("Название");
    nameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dialogLayout->addWidget(nameLabel);

    this->nameText = new QLineEdit(addDialog);
    nameText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    nameText->setStyleSheet(
            "background-color: #1B1212;"
            "color: white;"
            "font-size: 14px;"
            "font-weight: bold;"
        );
    nameText->setFixedWidth(200);
    dialogLayout->addWidget(nameText);


    QLabel* nameOperatorLabel = new QLabel(addDialog);
    nameOperatorLabel->setText("Название оператора");
    nameOperatorLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dialogLayout->addWidget(nameOperatorLabel);

    this->nameOperatorText = new QLineEdit(addDialog);
    nameOperatorText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    nameOperatorText->setStyleSheet(
            "background-color: #1B1212;"
            "color: white;"
            "font-size: 14px;"
            "font-weight: bold;"
        );
    nameOperatorText->setFixedWidth(200);
    dialogLayout->addWidget(nameOperatorText);
    QFrame* dialogButtonsFrame = new QFrame(addDialog);
    QHBoxLayout* dialogButtonsLayout = new QHBoxLayout(dialogButtonsFrame);
    dialogButtonsLayout->setContentsMargins(0, 0, 0, 0);
    dialogButtonsLayout->setSpacing(10);

    QPushButton* okButton = new QPushButton("Добавить", dialogButtonsFrame);
    okButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    okButton->setStyleSheet(
            "background-color: #1B1212;"
            "border-radius: 10px;"
        );
    dialogButtonsLayout->addWidget(okButton);
    QPushButton* cancelButton = new QPushButton("Отмена", dialogButtonsFrame);
    cancelButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    cancelButton->setStyleSheet(
            "background-color: #1B1212;"
            "border-radius: 10px;"
        );
    dialogButtonsLayout->addWidget(cancelButton);
    dialogLayout->addWidget(dialogButtonsFrame);
    dialogLayout->addStretch();


    connect(okButton, &QPushButton::clicked, this, &MainWindow::OnOkDialogButtonClicked);
}

void MainWindow::CreateWidgets()
{
    InitAddButtonDialog();
    QLayout* centralWidgetLayout = this->centralWidget()->layout();
    if (centralWidgetLayout)
    {
        centralWidgetLayout->setContentsMargins(0, 0, 0, 0);
    }

    QFrame* mainFrame = new QFrame(this);
    mainFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainFrame->setFrameShape(QFrame::NoFrame);
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
            "border-radius: 15px;"
            "padding: 4px;"
            "font-size: 14px;"
            "font-weight: bold;"
        );

    tableLabel->setText("Список доступных профилей eSIM");
    tableViewLayout->addWidget(tableLabel, 0, 0, 1, 3, Qt::AlignCenter);


    QTableView* currentProfilesTableView = new QTableView(mainFrame);
    this->tableController = new TableController(this, currentProfilesTableView);
    //    if (tableController.IsEmpty())
    //    {
    //        QMessageBox::information(this, "Предупреждение", "Нет доступных профилей");
    //    }
    tableViewLayout->addWidget(currentProfilesTableView, 1, 0, 4, 3);

    QFrame* buttonsFrame = new QFrame(mainFrame);
    tableViewLayout->addWidget(buttonsFrame, 4, 4, 1, 1);

    QVBoxLayout* buttonsLayout = new QVBoxLayout(buttonsFrame);
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsFrame->setLayout(buttonsLayout);
    addButton = new QPushButton("Добавить профиль", buttonsFrame);
    addButton->setFixedHeight(40);
    deleteButton = new QPushButton("Удалить выбранный профиль", buttonsFrame);
    deleteButton->setFixedHeight(40);
    refreshButton = new QPushButton("Обновить список", buttonsFrame);
    refreshButton->setFixedHeight(40);
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
    connect(this->addButton, &QPushButton::clicked, this, &MainWindow::OnAddButtonClicked);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    CreateWidgets();
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
    delete tableController;
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

void MainWindow::OnAddButtonClicked()
{
        addDialog->show();
        addDialog->raise();
        addDialog->activateWindow();
}

void MainWindow::OnOkDialogButtonClicked()
{
    QString name = nameText->text();
    QString nameOperator = nameOperatorText->text();

    tableController->AddProfile(name, nameOperator);
    nameText->clear();
    nameOperatorText->clear();

    if (addDialog) {
        addDialog->close();
    }
}
