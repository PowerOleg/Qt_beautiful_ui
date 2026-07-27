#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>
#include <QSizePolicy>

class QWidget;
class QLabel;
class QLineEdit;
class QPushButton;
class QDialog;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QTableView;
class QStackedWidget;
class QSpacerItem;

struct ThemePalette {
    QString bgMain;
    QString bgButton;
    QString textColor;
    QString borderColor;
    QString hoverColor;
};


inline const ThemePalette greenPalette = {
    "#1B1212", "#228B22", "white", "#1B1212", "rgba(255, 0, 0, 0.2)"
};

inline const ThemePalette bluePalette = {
    "#0B1F33", "#4A7FA8", "white", "#0B1F33", "rgba(255, 255, 255, 0.3)"
};

class Factory : public QObject
{
    Q_OBJECT
public:
    explicit Factory(const ThemePalette &palette, QObject *parent = nullptr) : palette(palette), QObject(parent) {}
    virtual ~Factory() {}

    virtual QVBoxLayout* createVBoxLayout(QWidget *parent) = 0;
    virtual QHBoxLayout* createHBoxLayout(QWidget *parent) = 0;
    virtual QGridLayout* createGridLayout(QWidget *parent) = 0;
    virtual QFrame* createFrame(QWidget *parent) = 0;
    virtual QTableView* createTableView() = 0;
    virtual QStackedWidget* createStackedWidget(QWidget *parent) = 0;
    virtual QSpacerItem* createSpacer(int w, int h,
                                       QSizePolicy::Policy hPolicy,
                                       QSizePolicy::Policy vPolicy) = 0;
    virtual QDialog* createDialog(QWidget *parent) = 0;
    virtual QLabel* createLabel(QWidget *parent) = 0;
    virtual QLineEdit* createLineEdit(QWidget *parent) = 0;
    virtual QPushButton* createPushButton(QWidget *parent) = 0;
    virtual QString getTableViewStyle() const = 0;
    virtual QString getGlobalBackgroundStyle() const = 0;
    virtual QString getHeaderStyle() const = 0;
    const ThemePalette& getPalette() const { return palette; }
protected:
    ThemePalette palette;
};

#endif // FACTORY_H
