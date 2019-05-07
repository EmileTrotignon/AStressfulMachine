//
// Created by emile on 08/04/19.
//

#ifndef A_STRESSFUL_MACHINE_GUIPICKSAVE_H
#define A_STRESSFUL_MACHINE_GUIPICKSAVE_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

class GameGUI;

using namespace std;

/**
 * This widget is used to display a list of available save and let you pick one
 */
class GUIPickSave : public QWidget
{

Q_OBJECT

public:

    explicit GUIPickSave(QWidget *parent_, GameGUI *game);

private:

    QListWidget *saves_list;
    QVBoxLayout *layout;
    GameGUI *game;
    QPushButton *back_button;

public slots:

    /**
     * Setup everything when the saved is picked and emit save_picked()
     * @param w The one lucky save.
     */
    void pick_save(QListWidgetItem *w);

signals:

    /**
     * Signal emitted when the user picked the save
     * Just used to give back the hand to the adventure mode widget as it doesnt have any parameter : the heavy lifting is done by the slot "pick_save"
     */
    void save_picked();

};


#endif //A_STRESSFUL_MACHINE_GUIPICKSAVE_H
