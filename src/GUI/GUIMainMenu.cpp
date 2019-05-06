//
// Created by marcel on 23/03/19.
//

#include "GUIMainMenu.h"
#include "GameGUI.h"

#include <QApplication>
#include <QSound>
#include <iostream>
#include <QMediaPlayer>
#include <QFileInfo>

GUIMainMenu::GUIMainMenu(QWidget *parent_) : QWidget(parent_)
{
    this->setObjectName(""); // For debugging purposes

    // QSound bells("../data/assets/sounds/Start_game.wav");
    QSound bells(QFileInfo("../data/assets/sounds/Start_game.wav").absoluteFilePath());
	bells.play();

    // Create font
    title_font.setFamily("arial");
    title_font.setPointSize(24);
    title_font.setBold(true);


    // Create title
    title = new QLabel("A Stressful Machine", this);
    title->setAlignment(Qt::AlignCenter);
    title->setFont(title_font);
    // title->setStyleSheet("background-color: rgb(52, 255, 239)");

    // Create buttons
    adventure_mode_button = new QPushButton("Adventure Mode", this);
    sandbox_button = new QPushButton("Sandbox mode", this);

    quit_game_button = new QPushButton("Quit Game", this);

	play_music_button = new QPushButton("Play Song", this);
	stop_music_button = new QPushButton("Stop Song", this);
	
	// Songs
    sound = new QSound("../data/assets/sounds/Start_game.wav");
	level_w = new QMediaPlayer;
	level_w->setMedia(QUrl::fromLocalFile(QFileInfo("../data/assets/sounds/Game_song.wav").absoluteFilePath()));
	
    // Insert buttons in button layout
    button_layout = new QVBoxLayout;
    button_layout->setObjectName("button_layout");

    button_layout->addWidget(adventure_mode_button);
    button_layout->addWidget(sandbox_button);
    button_layout->addWidget(play_music_button);
    button_layout->addWidget(stop_music_button);
    button_layout->addWidget(quit_game_button);


    // Create main layout
    window_Layout = new QGridLayout(this);
    window_Layout->setObjectName("window_Layout");
    window_Layout->addLayout(button_layout, 3, 1, 1, 1);
    window_Layout->addWidget(title, 1, 0, 1, 3);
    window_Layout->setRowStretch(0, 1);
    window_Layout->setRowStretch(2, 1);
    window_Layout->setRowStretch(4, 1);
    window_Layout->setColumnStretch(2, 1);
    window_Layout->setColumnStretch(0, 1);

    // window_Layout->setVerticalSpacing(0);

    // Set window layout
    // this->setLayout(window_Layout);


    // Create events
    connect(quit_game_button, SIGNAL (clicked(bool)), QApplication::instance(), SLOT (quit()));
    connect(adventure_mode_button, SIGNAL(clicked(bool)), parent(), SLOT (open_adventure_mode()));
    //connect(new_game_button, SIGNAL (clicked(bool)), this, SLOT (createNewGameDialog()));
    connect(sandbox_button, SIGNAL(clicked(bool)), parent(), SLOT (open_sandbox()));
	connect(play_music_button, SIGNAL(clicked(bool)), this, SLOT(song_on()));
	connect(stop_music_button, SIGNAL(clicked(bool)), this, SLOT(song_off()));
}

GUIMainMenu::~GUIMainMenu()

{
    // Does this call parent's destructor?
    std::cout << "Destructing GUIWindowMainMenu" << std::endl;
    delete button_layout;
}

void GUIMainMenu::song_on()
{
	//sound->play();
	//level_w->play();
	
	// level_w->setMedia(QUrl::fromLocalFile("../data/assets/sounds/Game_song.wav"));
	level_w->setVolume(50);
	//level_w->play();

	if (level_w->state() == QMediaPlayer::PlayingState) {
		level_w->setPosition(0);
		level_w->stop();
	}
	else if (level_w->state() == QMediaPlayer::StoppedState) {
		level_w->play();
	}

}

void GUIMainMenu::song_off()
{
	//sound->stop();
	level_w->stop();
}

/*void GUIMainMenu::createNewGameDialog()
{
    new_game_dialog = new QInputDialog(this);
    new_game_dialog->setObjectName("new_game_dialog");
    new_game_dialog->setWindowTitle("Create a new save");
    new_game_dialog->setInputMode(QInputDialog::TextInput);
    new_game_dialog->setLabelText("Name:");
    new_game_dialog->show();

    connect(new_game_dialog, SIGNAL (accepted()), parent(), SLOT (create_new_game_window()));
}*/
