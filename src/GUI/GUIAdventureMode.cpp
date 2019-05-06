//
// Created by emile on 09/04/19.
//

#include "GUIAdventureMode.h"
#include "GameGUI.h"
#include <QSound>
#include <QFileInfo>

GUIAdventureMode::GUIAdventureMode(GameGUI *game_) : QStackedWidget(game_), game(game_), level_picker(nullptr),
                                                     game_widget(nullptr)
{
    setObjectName("Adventure Mode Object");

    save_picker = new GUIPickSave(this, game);

    addWidget(save_picker);

    setCurrentWidget(save_picker);

    connect(save_picker, SIGNAL(save_picked()), this, SLOT(pick_level()));
}

void GUIAdventureMode::pick_save()
{
    setCurrentWidget(save_picker);
}

void GUIAdventureMode::pick_level()
{
    if (level_picker == nullptr)
    {
        level_picker = new GUIPickLevel(this, game);
        addWidget(level_picker);
    }
    setCurrentWidget(level_picker);

    connect(level_picker, SIGNAL(level_picked()), this, SLOT(launch_game()));

}

void GUIAdventureMode::launch_game()
{
    // QSound bells("../data/assets/sounds/Start_game.wav");
    QSound bells(QFileInfo(
            QString::fromStdString((game->gamefiles_dir / "../assets/sounds/Start_game.wav"))).absoluteFilePath());
	bells.play();
    if (game_widget == nullptr)
    {
        game_widget = new GUIGameplay(this, game);
        addWidget(game_widget);
    }
    setCurrentWidget(game_widget);
}

void GUIAdventureMode::return_pick_save()
{
    setCurrentWidget(save_picker);
}

/**
 * Dialog triggered by pressing esc in adventure mode
 */
void GUIAdventureMode::open_esc_dialog()
{
    auto esc_dlg = new QDialog(this);
    esc_dlg->setObjectName("Escape dialog");
    esc_dlg->setWindowTitle("A Stressful Machine");
    // esc_menu = new QDialogButtonBox(QDialogButtonBox::Close | QDialogButtonBox::Ok, Qt::Vertical, esc_dlg);
    auto resume_button = new QPushButton("Resume", esc_dlg);
    auto load_save_button = new QPushButton("Load save", esc_dlg);
    auto switch_level_button = new QPushButton("Switch levels", esc_dlg);
    auto quit_button = new QPushButton("Quit to main menu", esc_dlg);
    auto layout = new QVBoxLayout(esc_dlg);

    layout->addWidget(resume_button);
    layout->addWidget(switch_level_button);
    layout->addWidget(load_save_button);
    layout->addWidget(quit_button);

    if (currentWidget() != game_widget)
    {
        switch_level_button->setEnabled(false);
        if (currentWidget() == save_picker) load_save_button->setEnabled(false);
    }

    esc_dlg->setModal(true);
    esc_dlg->open();

    connect(switch_level_button, SIGNAL(clicked(bool)), this, SLOT(pick_level()));
    connect(switch_level_button, SIGNAL(clicked(bool)), parent(), SLOT(close_esc_dialog()));

    connect(load_save_button, SIGNAL(clicked(bool)), this, SLOT(pick_save()));
    connect(load_save_button, SIGNAL(clicked(bool)), parent(), SLOT(close_esc_dialog()));


    connect(resume_button, SIGNAL (clicked(bool)), parent(), SLOT (close_esc_dialog()));
    connect(parent(), SIGNAL (resume_game(int)), esc_dlg, SLOT (done(int)));

    qDebug() << parent();
    connect(quit_button, SIGNAL (clicked(bool)), parent(), SLOT (esc_dialog_quit()));
}
