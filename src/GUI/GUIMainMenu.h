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
#include <QSound>
#include <QMediaPlayer>

// class QPushButton;
class GUIMainMenu : public QWidget
{
    // Initialize macro for qt
    Q_OBJECT

public:
    explicit GUIMainMenu(QWidget *parent_ = nullptr);

    ~GUIMainMenu() override;


private slots:

	// Used in GUIMainMenu
	void song_on();

	void song_off();

private:
    QGridLayout *window_Layout;
    QVBoxLayout *button_layout;
    QLabel *title;
    QFont title_font;
    QPushButton *adventure_mode_button;
    QPushButton *sandbox_button;
    QPushButton *settings_button;
    QPushButton *quit_game_button;
	QPushButton * play_music_button;
	QPushButton * stop_music_button;
	QSound* sound;
	QMediaPlayer* level_w;
};


#endif //A_STRESSFUL_MACHINE_GUIWINDOWMAINMENU_H
