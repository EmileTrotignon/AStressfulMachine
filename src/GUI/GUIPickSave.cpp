//
// Created by emile on 08/04/19.
//

#include "GUIPickSave.h"
#include "GameGUI.h"

GUIPickSave::GUIPickSave(QWidget *parent_, GameGUI *game_) : QWidget(parent_), game(game_)
{

    layout = new QVBoxLayout(this);
    saves_list = new QListWidget(this);
    vector<string> saves = game->save_picker->get_saves();
    for (const string &s:saves)
    {
        new QListWidgetItem(QString::fromStdString(s), saves_list);
    }

    // Could make this interface prettier
    // saves_list->setMaximumSize(200, 200);

    connect(saves_list,
            SIGNAL(itemActivated(QListWidgetItem * )),
            this,
            SLOT(pick_save(QListWidgetItem * )));

    back_button = new QPushButton(this);
    back_button->setText("Back");

    connect(back_button, SIGNAL (clicked(bool)), parent()->parent(), SLOT (return_main_menu_from_pick_save()));

    layout->addWidget(saves_list);
    layout->addWidget(back_button);
}

void GUIPickSave::pick_save(QListWidgetItem *w)
{
    game->game_sequence = new GameSequence(game->save_picker->select_save(w->text().toStdString()));
    emit save_picked();
}
