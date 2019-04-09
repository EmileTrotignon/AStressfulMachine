//
// Created by emile on 09/04/19.
//

#include "GUIAdventureMode.h"
#include "GameGUI.h"

GUIAdventureMode::GUIAdventureMode(GameGUI *game_) : QStackedWidget(game_), game(game_)
{
    game_widget = new GUIGameplay(this);
    save_picker = new GUIPickSave(this, game);
    level_picker = nullptr;

    addWidget(game_widget);
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
}

void GUIAdventureMode::launch_game()
{
    setCurrentWidget(game_widget);
}
