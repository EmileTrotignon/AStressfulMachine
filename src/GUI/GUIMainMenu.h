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
#include <QInputDialog>

// class QPushButton;
class GUIMainMenu : public QWidget
{
    // Initialize macro for qt
    Q_OBJECT

public:
    explicit GUIMainMenu(QWidget *parent = nullptr);
    ~GUIMainMenu();

private slots:
    void createNewGameDialog();

private:
    QGridLayout *windowLayout;
    QVBoxLayout *buttonLayout;
    QLabel *title;
    QFont titleFont;
    QPushButton *newGameButton;
    QPushButton *loadGameButton;
    QPushButton *settingsButton;
    QPushButton *quitGameButton;
    QInputDialog *newGameDialog;
};


#endif //A_STRESSFUL_MACHINE_GUIWINDOWMAINMENU_H
