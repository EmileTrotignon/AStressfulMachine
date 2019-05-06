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
	// QSound bells("../data/assets/sons/Start_game.wav");
	QSound bells(QFileInfo("../data/assets/sons/Start_game.wav").absoluteFilePath());
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
