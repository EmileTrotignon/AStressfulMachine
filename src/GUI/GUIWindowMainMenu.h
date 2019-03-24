//
// Created by marcel on 23/03/19.
//

#ifndef A_STRESSFUL_MACHINE_GUIWINDOWMAINMENU_H
#define A_STRESSFUL_MACHINE_GUIWINDOWMAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

// class QPushButton;
class GUIWindowMainMenu : public QWidget
{
    // Initialize macro for qt
    Q_OBJECT
public:
    explicit GUIWindowMainMenu(QWidget *parent = nullptr);
    ~GUIWindowMainMenu();
private:
    QGridLayout *windowLayout;
    QVBoxLayout *buttonLayout;
    QLabel *title;
    QFont titleFont;
    QPushButton *newGameButton;
    QPushButton *loadGameButton;
    QPushButton *settingsButton;
    QPushButton *quitGameButton;
};


#endif //A_STRESSFUL_MACHINE_GUIWINDOWMAINMENU_H
