#ifndef REMOVEPROFILECOMMAND_H
#define REMOVEPROFILECOMMAND_H

#include "icommand.h"
#include "../esimmodel.h"

class RemoveProfileCommand : public ICommand
{
public:
    RemoveProfileCommand(ESimModel* model, int row)
        : model(model), row(row) {}

    void execute() override;
    void undo() override;
    QString name() const override;
private:
    ESimModel* model;
    int row;
    ItemModel removedItem;
};

#endif // REMOVEPROFILECOMMAND_H
