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
#include <QStackedWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tablecontroller.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    InitAddButtonDialog();
    CreateWidgets();
    InitMainWindowActions();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tableController;
}

/**
 * @brief Инициализирует диалог, который добавляет профиль eSIM в таблицу
 */
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

    connect(okButton, &QPushButton::clicked, this, &MainWindow::OnOkButtonDialogClicked);
    connect(cancelButton, &QPushButton::clicked, addDialog, &QDialog::reject);
}

/**
 * @brief Метод инициализирует виджеты, расположенные на главном диалоговом окне
 */
void MainWindow::CreateWidgets()
{
    QLayout* centralWidgetLayout = this->centralWidget()->layout();
    if (centralWidgetLayout)
    {
        centralWidgetLayout->setContentsMargins(0, 0, 0, 0);
    }
    QFrame* mainFrame = new QFrame(this);
    mainFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainFrame->setFrameShape(QFrame::NoFrame);
    centralWidgetLayout->addWidget(mainFrame);


    this->tableViewLayout = new QGridLayout(mainFrame);
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


    QTableView* currentProfilesTableView = new QTableView();
    tableStacked = new QStackedWidget(mainFrame);
    tableStacked->addWidget(currentProfilesTableView);
    QLabel* noProfilesLabel = new QLabel(mainFrame);
    noProfilesLabel->setStyleSheet(
            "background-color: #1B1212;"
            "color: red;"
            "font-size: 20px;"
            "font-weight: bold;"
    );
    noProfilesLabel->setText("Нет доступных профилей");
    tableStacked->addWidget(noProfilesLabel);
    tableViewLayout->addWidget(tableStacked, 1, 0, 4, 3);

    this->tableController = new TableController(this, currentProfilesTableView);
    //в зависимости от наличия данных в файле реализовна логика выбора отображаемого виджета: 0 - таблицы или 1- QLabel
    bool isReadFile = tableController->ReadFile(":/profiles.txt");
    if (isReadFile)
    {
        tableStacked->setCurrentIndex(0);
    }
    else
    {
        tableStacked->setCurrentIndex(1);
        tableStacked->setFixedHeight(40);
        noProfilesLabel->setAlignment(Qt::AlignCenter);
        tableViewLayout->setAlignment(tableStacked, Qt::AlignCenter | Qt::AlignTop);
    }

    QFrame* buttonsFrame = new QFrame(mainFrame);
    QVBoxLayout* buttonsLayout = new QVBoxLayout(buttonsFrame);
    buttonsFrame->setLayout(buttonsLayout);

    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    tableViewLayout->addWidget(buttonsFrame, 1, 4, 1, 1);
    addButton = new QPushButton("Добавить профиль", buttonsFrame);
    addButton->setFixedHeight(40);
    deleteButton = new QPushButton("Удалить выбранный профиль", buttonsFrame);
    deleteButton->setFixedHeight(40);
    refreshButton = new QPushButton("Обновить список", buttonsFrame);
    refreshButton->setFixedHeight(40);
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(deleteButton);
    buttonsLayout->addWidget(refreshButton);
    buttonsLayout->addStretch();

    QSpacerItem* spacerEnd = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    tableViewLayout->addItem(spacerEnd, 2, 0);
}

/**
 * @brief Метод инициализирует сигнало-слотовое взаимодействие для главного диалогового окна
 */
void MainWindow::InitMainWindowActions()
{
    connect(ui->minimizeWindowButton, &QPushButton::clicked, this, &QMainWindow::showMinimized);
    connect(ui->closeWindowButton, &QPushButton::clicked, this, &QMainWindow::close);
    connect(this->addButton, &QPushButton::clicked, this, &MainWindow::OnAddButtonClicked);
    connect(this->deleteButton, &QPushButton::clicked, tableController, &TableController::RemoveSelectedProfile);
    connect(this->refreshButton, &QPushButton::clicked, tableController, &TableController::RefreshTable);
}
/**
 * @brief Обработка зажатия левой кнопки мыши
 * @param event
 */
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

/**
 * @brief Обработка перетаскивания окна
 * @param event
 */
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

/**
 * @brief Обработчик нажатия на кнопку "Добавить профиль"
 */
void MainWindow::OnAddButtonClicked()
{
        addDialog->show();
        addDialog->raise();
        addDialog->activateWindow();
}

/**
 * @brief Обработчик нажатия на кнопку "Добавить" в диалоговом окне добавления профиля eSIM
 */
void MainWindow::OnOkButtonDialogClicked()
{
    int currentIndex = tableStacked->currentIndex();
    if (currentIndex == 1)
    {
        tableStacked->setCurrentIndex(0);
        tableStacked->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        tableViewLayout->setAlignment(tableStacked, Qt::AlignLeft | Qt::AlignTop);
        tableStacked->setMinimumSize(TABLE_WIDTH, TABLE_HEIGHT);
    }

    QString name = nameText->text();
    QString nameOperator = nameOperatorText->text();
    tableController->AddProfile(name, nameOperator);
    nameText->clear();
    nameOperatorText->clear();

    if (addDialog) {
        addDialog->close();
    }
}
