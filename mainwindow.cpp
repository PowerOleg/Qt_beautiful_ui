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
#include "esimmodel.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tablecontroller.h"
#include "./factory/greenfactory.h"
#include "./factory/bluefactory.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    factory = new GreenRoundFactory(this);
    initAddButtonDialog();
    createWidgets();
    initMainWindowActions();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tableController;
}

/**
 * @brief Инициализирует диалог, который добавляет профиль eSIM в таблицу
 */
void MainWindow::initAddButtonDialog()
{
    this->addDialog = factory->createDialog(this);
    QVBoxLayout* dialogLayout = factory->createVBoxLayout(addDialog);

    QLabel* nameLabel = factory->createLabel(addDialog);
    nameLabel->setText("Название");
    dialogLayout->addWidget(nameLabel);

    this->nameText = factory->createLineEdit(addDialog);
    dialogLayout->addWidget(nameText);

    QLabel* nameOperatorLabel = factory->createLabel(addDialog);
    nameOperatorLabel->setText("Название оператора");
    dialogLayout->addWidget(nameOperatorLabel);

    this->nameOperatorText = factory->createLineEdit(addDialog);
    dialogLayout->addWidget(nameOperatorText);

    QFrame* dialogButtonsFrame = factory->createFrame(addDialog);
    QHBoxLayout* dialogButtonsLayout = factory->createHBoxLayout(dialogButtonsFrame);

    QPushButton* okButton = factory->createPushButton(dialogButtonsFrame);
    okButton->setText("Добавить");
    dialogButtonsLayout->addWidget(okButton);

    QPushButton* cancelButton = factory->createPushButton(dialogButtonsFrame);
    cancelButton->setText("Отмена");
    dialogButtonsLayout->addWidget(cancelButton);

    dialogLayout->addWidget(dialogButtonsFrame);
    dialogLayout->addStretch();

    connect(okButton, &QPushButton::clicked, this, &MainWindow::onOkButtonDialogClicked);
    connect(cancelButton, &QPushButton::clicked, addDialog, &QDialog::reject);
}

/**
 * @brief Метод инициализирует виджеты, расположенные на главном диалоговом окне
 */
void MainWindow::createWidgets()
{
    this->setStyleSheet(factory->getGlobalBackgroundStyle());
    ui->headerWidget->setStyleSheet(factory->getHeaderStyle());

    QLayout* centralWidgetLayout = this->centralWidget()->layout();
    if (centralWidgetLayout)
        centralWidgetLayout->setContentsMargins(0, 0, 0, 0);

    QFrame* mainFrame = factory->createFrame(this);
    mainFrame->setStyleSheet(factory->getTableViewStyle());
    centralWidgetLayout->addWidget(mainFrame);
    this->tableViewLayout = factory->createGridLayout(mainFrame);
    tableViewLayout->setContentsMargins(10, 10, 10, 10);
    mainFrame->setLayout(tableViewLayout);

    QLabel* tableLabel = factory->createLabel(mainFrame);
    tableLabel->setText("Список доступных профилей eSIM");
    tableViewLayout->addWidget(tableLabel, 0, 0, 1, 3, Qt::AlignCenter);

    QTableView* currentProfilesTableView = factory->createTableView();
    tableStacked = factory->createStackedWidget(mainFrame);
    tableStacked->addWidget(currentProfilesTableView);
    QLabel* noProfilesLabel = factory->createLabel(mainFrame);

    noProfilesLabel->setText("Нет доступных профилей");
    tableStacked->addWidget(noProfilesLabel);
    tableViewLayout->addWidget(tableStacked, 1, 0, 4, 3);

    this->tableController = new TableController(this, currentProfilesTableView);
    bool isReadFile = tableController->readFile(":/profiles.txt");

    if (isReadFile) {
        tableStacked->setCurrentIndex(0);
    } else {
        tableStacked->setCurrentIndex(1);
        tableStacked->setFixedHeight(40);
        noProfilesLabel->setAlignment(Qt::AlignCenter);
        tableViewLayout->setAlignment(tableStacked, Qt::AlignCenter | Qt::AlignTop);
    }

    QFrame* buttonsFrame = factory->createFrame(mainFrame);
    QVBoxLayout* buttonsLayout = factory->createVBoxLayout(buttonsFrame);
    buttonsFrame->setLayout(buttonsLayout);
    buttonsLayout->setContentsMargins(0, 0, 0, 0);

    tableViewLayout->addWidget(buttonsFrame, 1, 4, 1, 1);

    addButton = factory->createPushButton(buttonsFrame);
    addButton->setText("Добавить профиль");
    addButton->setFixedHeight(40);

    deleteButton = factory->createPushButton(buttonsFrame);
    deleteButton->setText("Удалить выбранный профиль");
    deleteButton->setFixedHeight(40);

    checkButton = factory->createPushButton(buttonsFrame);
    checkButton->setText("Проверить актуальность");
    checkButton->setFixedHeight(40);

    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(deleteButton);
    buttonsLayout->addWidget(checkButton);
    buttonsLayout->addStretch();

    QSpacerItem* spacerEnd = factory->createSpacer(20, 20,
                                            QSizePolicy::Expanding,
                                            QSizePolicy::Expanding);
    tableViewLayout->addItem(spacerEnd, 2, 0);
}

/**
 * @brief Метод инициализирует сигнало-слотовое взаимодействие для главного диалогового окна
 */
void MainWindow::initMainWindowActions()
{
    connect(ui->minimizeWindowButton, &QPushButton::clicked, this, &QMainWindow::showMinimized);
    connect(ui->closeWindowButton, &QPushButton::clicked, this, &QMainWindow::close);
    connect(this->addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    connect(this->deleteButton, &QPushButton::clicked, tableController, &TableController::removeSelectedProfile);
    connect(this->checkButton, &QPushButton::clicked, tableController, &TableController::checkTable);
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
void MainWindow::onAddButtonClicked()
{
        addDialog->show();
        addDialog->raise();
        addDialog->activateWindow();
}

/**
 * @brief Обработчик нажатия на кнопку "Добавить" в диалоговом окне добавления профиля eSIM
 */
void MainWindow::onOkButtonDialogClicked()
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
    ItemModel localAddProfile = tableController->addProfile(name, nameOperator);
    nameText->clear();
    nameOperatorText->clear();

    if (addDialog)
    {
        addDialog->close();
    }
}
