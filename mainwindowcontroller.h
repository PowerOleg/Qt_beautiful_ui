#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>

class Profile;
class QWidget;
class QGridLayout;

class MainWindowController
{
public:
    MainWindowController(/*QGridLayout* chosen_profile_layout = nullptr*/);
//    bool SetChosenProfile(Profile *parent);
//    void ClearChosenProfile();
private:
//    QGridLayout* chosen_profile_layout = nullptr;
};

#endif // MAINWINDOWCONTROLLER_H
