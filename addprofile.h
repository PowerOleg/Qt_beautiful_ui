#ifndef ADDPROFILE_H
#define ADDPROFILE_H

#include <QDialog>

namespace Ui {
class AddProfile;
}

class AddProfile : public QDialog
{
    Q_OBJECT

public:
    explicit AddProfile(QWidget *parent = nullptr);
    ~AddProfile();

private:
    Ui::AddProfile *ui;
};

#endif // ADDPROFILE_H
