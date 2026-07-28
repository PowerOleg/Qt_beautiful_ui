#ifndef ADDPROFILECOMMAND_H
#define ADDPROFILECOMMAND_H

#include "icommand.h"
#include "../esimmodel.h"

class AddProfileCommand : public ICommand
{
public:
    AddProfileCommand(ESimModel* model, const ItemModel& item)
        : model(model), item(item), row(-1) {}

    void execute() override;
    void undo() override;
    QString name() const override;
private:
    ESimModel* model;
    ItemModel item;
    int row;
};

#endif // ADDPROFILECOMMAND_H
