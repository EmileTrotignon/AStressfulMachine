//
// Created by emile on 09/04/19.
//

#include "GUIPickLevel.h"
#include "GameGUI.h"

GUIPickLevel::GUIPickLevel(QWidget *parent_, GameGUI *game_) : QWidget(parent_), game(game_)
{

    levels_list = new QListWidget(this);
    layout = new QVBoxLayout(this);
    vector<string> levels = game->game_sequence->get_available_levels();
    for (const string &s:levels)
    {
        new QListWidgetItem(QString::fromStdString(s), levels_list);
    }

    connect(levels_list,
            SIGNAL(itemActivated(QListWidgetItem * )),
            this,
            SLOT(pick_level(QListWidgetItem * )));

    back_button = new QPushButton(this);
    back_button->setText("Back");

    connect(back_button, SIGNAL (clicked(bool)), parent(), SLOT (return_pick_save()));

    layout->addWidget(levels_list);
    layout->addWidget(back_button);

}

void GUIPickLevel::pick_level(QListWidgetItem *w)
{
    game->game_sequence->select_level(w->text().toStdString());
    emit level_picked();
}