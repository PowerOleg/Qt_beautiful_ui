#include "addprofilecommand.h"

QString AddProfileCommand::name() const
{
    return QString("AddProfile at row %1").arg(row);
}

void AddProfileCommand::execute()
{
    row = model->rowCount();
    model->addItemModel(item);
}

void AddProfileCommand::undo()
{
    if (row >= 0 && row < model->rowCount())
    {
        model->removeItemModel(row);
    }
}


