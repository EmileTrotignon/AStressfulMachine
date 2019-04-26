//
// Created by emile on 06/03/19.
//

#include "GameGUI.h"

GameGUI::GameGUI(const string &saves_dir_, const string &gamefiles_dir_) : QMainWindow(nullptr),
                                                                           Game(saves_dir_, gamefiles_dir_),
                                                                           adventure_mode_widget(nullptr),
                                                                           sandbox(nullptr)
{
    qDebug() << "Constructing GameGUI";
    setObjectName("GUIWindow");
    setWindowTitle("A Stressful Machine");

    main_menu_widget = new GUIMainMenu(this);

    setCentralWidget(main_menu_widget);

    qDebug() << "Creating shortcut";
    auto *shortcut = new QShortcut(this);
    shortcut->setKey(Qt::Key_Escape);
    connect(shortcut, SIGNAL (activated()), this, SLOT (open_esc_menu()));
}


void GameGUI::play()
{
    show();
}

void GameGUI::open_adventure_mode()
{
    delete adventure_mode_widget;
    adventure_mode_widget = new GUIAdventureMode(this);
    setCentralWidget(adventure_mode_widget);
}

void GameGUI::open_sandbox()
{
    delete sandbox;
    sandbox = new GUISandbox(this);
    setCentralWidget(sandbox);
}

void GameGUI::open_esc_menu()
{

    qDebug() << "Esc shortcut pressed";

    if (centralWidget() != main_menu_widget)
    {
        auto esc_dlg = new QDialog(centralWidget());
        esc_dlg->setObjectName("Escape dialog");
        esc_dlg->setWindowTitle("A Stressful Machine");
        // esc_menu = new QDialogButtonBox(QDialogButtonBox::Close | QDialogButtonBox::Ok, Qt::Vertical, esc_dlg);
        auto esc_dlg_resume_button = new QPushButton("Resume", esc_dlg);
        auto esc_dlg_settings_button = new QPushButton("Settings", esc_dlg);
        auto esc_dlg_quit_button = new QPushButton("Quit to main menu", esc_dlg);
        auto esc_dlg_layout = new QVBoxLayout(esc_dlg);
        esc_dlg_layout->addWidget(esc_dlg_resume_button);
        esc_dlg_layout->addWidget(esc_dlg_settings_button);
        esc_dlg_layout->addWidget(esc_dlg_quit_button);
        esc_dlg->setModal(true);
        esc_dlg->open();

        // Connect resume button
        connect(esc_dlg_resume_button, SIGNAL (clicked(bool)), this, SLOT (esc_dlg_rejected()));
        connect(this, SIGNAL (resume_game(int)), esc_dlg, SLOT (done(int)));

        // Connect quit button
        connect(esc_dlg_quit_button, SIGNAL (clicked(bool)), this, SLOT (esc_dlg_quit()));
    }
}

void GameGUI::esc_dlg_rejected()
{
    emit resume_game();
}

void GameGUI::esc_dlg_quit()
{
    setCentralWidget(main_menu_widget);
    emit resume_game();
}

void GameGUI::return_main_menu_from_pick_save()
{
    setCentralWidget(main_menu_widget);
}
