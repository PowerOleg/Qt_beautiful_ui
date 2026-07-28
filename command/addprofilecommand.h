#ifndef ADDPROFILECOMMAND_H
#define ADDPROFILECOMMAND_H

#include "icommand.h"
#include "../esimmodel.h"

class AddProfileCommand : public ICommand
{
public:
    AddProfileCommand(ESimModel* model, const ItemModel& item)
        : m_model(model), m_item(item), m_row(-1) {}

    void execute() override
    {
        m_row = m_model->rowCount();
        m_model->addItemModel(m_item);
    }

    void undo() override
    {
        if (m_row >= 0 && m_row < m_model->rowCount())
        {
            m_model->removeItemModel(m_row);
        }
    }

private:
    ESimModel* m_model;
    ItemModel m_item;
    int m_row;
};

#endif // ADDPROFILECOMMAND_H
