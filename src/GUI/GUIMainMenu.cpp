//
// Created by marcel on 23/03/19.
//

#include "GUIMainMenu.h"
#include "GameGUI.h"

#include <QApplication>
#include <iostream>

GUIMainMenu::GUIMainMenu(QWidget *parent_) : QWidget(parent_)
{
    this->setObjectName("this"); // For debugging purposes

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
    new_game_button = new QPushButton("New Game", this);
    sandbox_button = new QPushButton("Sandbox mode", this);

    // new_game_button->setGeometry(10, 10, 100, 40);
    load_game_button = new QPushButton("Load Game", this);
    settings_button = new QPushButton("Settings", this);
    quit_game_button = new QPushButton("Quit Game", this);
    // quit_game_button->setGeometry(10, 60, 100, 40);

    // Insert buttons in button layout
    button_layout = new QVBoxLayout;
    button_layout->setObjectName("button_layout");
    // button_layout->setSpacing(6);
    button_layout->addWidget(new_game_button);
    button_layout->addWidget(load_game_button);
    button_layout->addWidget(sandbox_button);
    button_layout->addWidget(settings_button);
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
    connect(new_game_button, SIGNAL (clicked(bool)), this, SLOT (createNewGameDialog()));
    connect(sandbox_button, SIGNAL(clicked(bool)), parent(), SLOT (open_sandbox()));
}

GUIMainMenu::~GUIMainMenu()

{
    // Does this call parent's destructor?
    std::cout << "Destructing GUIWindowMainMenu" << std::endl;
    delete button_layout;
}

void GUIMainMenu::createNewGameDialog()
{
    new_game_dialog = new QInputDialog(this);
    new_game_dialog->setObjectName("new_game_dialog");
    new_game_dialog->setWindowTitle("Create a new save");
    new_game_dialog->setInputMode(QInputDialog::TextInput);
    new_game_dialog->setLabelText("Name:");
    new_game_dialog->show();

    connect(new_game_dialog, SIGNAL (accepted()), parent(), SLOT (create_new_game_window()));
}
