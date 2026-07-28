#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <QString>

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;

    virtual QString name() const { return "Command"; }//имя команды если еще записывать в логи
};

#endif // ICOMMAND_H
