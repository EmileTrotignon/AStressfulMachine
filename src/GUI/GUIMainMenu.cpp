//
// Created by marcel on 23/03/19.
//

#include "GUIMainMenu.h"

#include <QApplication>
#include <iostream>

GUIMainMenu::GUIMainMenu(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("this"); // For debugging purposes

    // Create font
    titleFont.setFamily("arial");
    titleFont.setPointSize(24);
    titleFont.setBold(true);


    // Create title
    title = new QLabel("A Stressful Machine", this);
    title->setAlignment(Qt::AlignCenter);
    title->setFont(titleFont);
    // title->setStyleSheet("background-color: rgb(52, 255, 239)");

    // Create buttons
    newGameButton = new QPushButton("New Game", this);
    // newGameButton->setGeometry(10, 10, 100, 40);
    loadGameButton = new QPushButton("Load Game", this);
    settingsButton = new QPushButton("Settings", this);
    quitGameButton = new QPushButton("Quit Game", this);
    // quitGameButton->setGeometry(10, 60, 100, 40);

    // Insert buttons in button layout
    buttonLayout = new QVBoxLayout;
    buttonLayout->setObjectName("buttonLayout");
    // buttonLayout->setSpacing(6);
    buttonLayout->addWidget(newGameButton);
    buttonLayout->addWidget(loadGameButton);
    buttonLayout->addWidget(settingsButton);
    buttonLayout->addWidget(quitGameButton);

    // Create main layout
    windowLayout = new QGridLayout(this);
    windowLayout->setObjectName("windowLayout");
    windowLayout->addLayout(buttonLayout, 3, 1, 1, 1);
    windowLayout->addWidget(title, 1, 0, 1, 3);
    windowLayout->setRowStretch(0, 1);
    windowLayout->setRowStretch(2, 1);
    windowLayout->setRowStretch(4, 1);
    windowLayout->setColumnStretch(2, 1);
    windowLayout->setColumnStretch(0, 1);

    // windowLayout->setVerticalSpacing(0);

    // Set window layout
    // this->setLayout(windowLayout);


    // Create events
    connect(quitGameButton, SIGNAL (clicked(bool)), QApplication::instance(), SLOT (quit()));
    connect(newGameButton, SIGNAL (clicked(bool)), this, SLOT (createNewGameDialog()));
}

GUIMainMenu::~GUIMainMenu()

{
    // Does this call parent's destructor?
    std::cout << "Destructing GUIWindowMainMenu" << std::endl;
    delete buttonLayout;
}

void GUIMainMenu::createNewGameDialog()
{
    newGameDialog = new QInputDialog(this);
    newGameDialog->setObjectName("newGameDialog");
    newGameDialog->setWindowTitle("Create a new save");
    newGameDialog->setInputMode(QInputDialog::TextInput);
    newGameDialog->setLabelText("Name:");
    newGameDialog->show();

    connect(newGameDialog, SIGNAL (accepted()), parent() , SLOT (createNewGameWindow()));
}
