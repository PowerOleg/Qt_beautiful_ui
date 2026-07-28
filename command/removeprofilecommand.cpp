#include "removeprofilecommand.h"

QString RemoveProfileCommand::name() const
{
    return QString("RemoveProfile at row %1").arg(row);
}

void RemoveProfileCommand::execute()
{
    removedItem = model->removeItemModel(row);
}

void RemoveProfileCommand::undo()
{
    model->insertItemModelAt(row, removedItem);
}

