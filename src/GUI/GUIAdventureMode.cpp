//
// Created by emile on 09/04/19.
//

#include "GUIAdventureMode.h"
#include "GameGUI.h"

GUIAdventureMode::GUIAdventureMode(GameGUI *game) : QStackedWidget(game)
{
    game_widget = new GUIGameplay(this);
    save_picker = new GUIPickSave(this, game);
    level_picker = new GUIPickLevel(this);

    addWidget(game_widget);
    addWidget(save_picker);
    addWidget(level_picker);

    setCurrentWidget(save_picker);
}

void GUIAdventureMode::pick_save()
{
    setCurrentWidget(save_picker);
}

void GUIAdventureMode::pick_level()
{
    setCurrentWidget(level_picker);
}

void GUIAdventureMode::launch_game()
{
    setCurrentWidget(game_widget);
}
