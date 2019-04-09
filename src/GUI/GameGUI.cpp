//
// Created by emile on 06/03/19.
//

#include "GameGUI.h"

GameGUI::GameGUI(const string &saves_dir_, const string &gamefiles_dir_) : QStackedWidget(nullptr),
                                                                           Game(saves_dir_, gamefiles_dir_)
{
    qDebug() << "Constructing GameGUI";
    setObjectName("GUIWindow");
    setWindowTitle("A Stressful Machine");

    // Create the tree windows
    main_menu_widget = new GUIMainMenu(this);
    adventure_mode_widget = new GUIAdventureMode(this);
    sandbox = new GUISandbox(this);

    // Add them to the stack
    addWidget(main_menu_widget);
    addWidget(adventure_mode_widget);
    addWidget(sandbox);

    setCurrentWidget(main_menu_widget);

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
    setCurrentWidget(adventure_mode_widget);
}

void GameGUI::open_sandbox()
{
    setCurrentWidget(sandbox);
}

void GameGUI::open_esc_menu()
{

    qDebug() << "Esc shortcut pressed";

    if (currentWidget() != main_menu_widget)
    {
        auto esc_dlg = new QDialog(currentWidget());
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
        connect(this, SIGNAL (resume_play(int)), esc_dlg, SLOT (done(int)));

        // Connect quit button
        connect(esc_dlg_quit_button, SIGNAL (clicked(bool)), this, SLOT (esc_dlg_quit()));
    }
}

void GameGUI::esc_dlg_rejected()
{
    emit resume_play();
}

void GameGUI::esc_dlg_quit()
{
    setCurrentWidget(main_menu_widget);
    emit resume_play();
}