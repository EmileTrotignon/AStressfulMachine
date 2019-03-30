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
    explicit GUIMainMenu(QWidget *parent_ = nullptr);

    ~GUIMainMenu() override;

private slots:
    void createNewGameDialog();

private:
    QGridLayout *window_Layout;
    QVBoxLayout *button_layout;
    QLabel *title;
    QFont title_font;
    QPushButton *new_game_button;
    QPushButton *new_sandbox_button;
    QPushButton *load_game_button;
    QPushButton *settings_button;
    QPushButton *quit_game_button;
    QInputDialog *new_game_dialog;
};


#endif //A_STRESSFUL_MACHINE_GUIWINDOWMAINMENU_H
