#include "addprofile.h"
#include "ui_addprofile.h"

AddProfile::AddProfile(QWidget *parent) : QDialog(parent), ui(new Ui::AddProfile)
{
    ui->setupUi(this);
}

AddProfile::~AddProfile()
{
    delete ui;
}
