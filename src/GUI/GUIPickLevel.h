//
// Created by emile on 09/04/19.
//

#ifndef A_STRESSFUL_MACHINE_GUIPICKLEVEL_H
#define A_STRESSFUL_MACHINE_GUIPICKLEVEL_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

class GameGUI;

/**
 * This widget is used to display a list of available save and let you pick one
 */
class GUIPickLevel : public QWidget
{

Q_OBJECT

public :

    explicit GUIPickLevel(QWidget *parent, GameGUI *game);

private:

    QListWidget *levels_list;
    QVBoxLayout *layout;
    QPushButton *back_button;
    GameGUI *game;

public slots:


    /**
     * Setup everything when the level is picked and emit level_picked()
     * @param w The one lucky level.
     */
    void pick_level(QListWidgetItem *w);

signals:

    /**
     * Signal emitted when the user picked the level
     * Just used to give back the hand to the adventure mode widget as it doesnt have any parameter : the heavy lifting is done by the slot "pick_level"
     */
    void level_picked();
};


#endif //A_STRESSFUL_MACHINE_GUIPICKLEVEL_H
