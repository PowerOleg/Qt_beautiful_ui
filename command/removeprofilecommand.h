#ifndef REMOVEPROFILECOMMAND_H
#define REMOVEPROFILECOMMAND_H


#include "icommand.h"
#include "../esimmodel.h"

class RemoveProfileCommand : public ICommand
{
public:
    RemoveProfileCommand(ESimModel* model, int row)
        : m_model(model), m_row(row) {}

    void execute() override
    {
        m_removedItem = m_model->removeItemModel(m_row);
    }

    void undo() override
    {
        m_model->insertItemModelAt(m_row, m_removedItem);
    }

private:
    ESimModel* m_model;
    int m_row;
    ItemModel m_removedItem;
};

#endif // REMOVEPROFILECOMMAND_H
