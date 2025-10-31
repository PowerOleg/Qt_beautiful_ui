#ifndef PROFILE_H
#define PROFILE_H

//#include <QWidget>
#include <QFrame>

class QRadioButton;
class QPushButton;
class QGridLayout;

class Profile : public QFrame//QWidget
{
    Q_OBJECT
public:
    explicit Profile(/*QWidget*/QFrame *parent = nullptr);
    QRadioButton* radio_button;

signals:

};
/* Ui::ESim *m_ui = nullptr;
//    QCheckBox select_box;
//    QLabel description;*/
#endif // PROFILE_H
