#ifndef ADDPROFILE_H
#define ADDPROFILE_H

#include <QWidget>

namespace Ui {
class AddProfile;
}

class AddProfile : public QWidget
{
    Q_OBJECT

public:
    explicit AddProfile(QWidget *parent = nullptr);
    ~AddProfile();

private:
    Ui::AddProfile *ui;
};

#endif // ADDPROFILE_H
