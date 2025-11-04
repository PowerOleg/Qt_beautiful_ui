//#include <QMessageBox>
#include <QWidget>
//#include <QGridLayout>
#include "tablecontroller.h"

TableController::TableController(/*QGridLayout* layout*/)// : chosen_profile_layout(layout)
{}

//bool MainWindowController::SetChosenProfile(Profile* profile)
//{
//    if (profile)
//    {
//        profile->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//        profile->setFixedHeight(200);
//        profile->setFixedWidth(300);
//        chosen_profile_layout->addWidget(profile, 0, 0, Qt::AlignLeft);
//        return true;
//    }
//    return false;
//}

//void MainWindowController::ClearChosenProfile()
//{
//    while (chosen_profile_layout->count() > 0)
//    {
//        QLayoutItem* item = chosen_profile_layout->takeAt(0);
//        if (item->widget())
//        {
//            delete item->widget();//удаляем виджет
//        }
//        delete item;//удаляем QLayoutItem
//    }
//}
