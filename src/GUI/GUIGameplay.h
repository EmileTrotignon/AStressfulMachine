//
// Created by marcel on 25/03/19.
//

#ifndef A_STRESSFUL_MACHINE_GUIWINDOWGAMEPLAY_H
#define A_STRESSFUL_MACHINE_GUIWINDOWGAMEPLAY_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QFont>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include "GUISandbox.h"

class GameGUI;

class GameLevel;

/**
 * Derived class from sandbox that add behaviour to actually play the game and not just program
 */
class GUIGameplay : public GUISandbox
{
    // Initialize macro for qt
Q_OBJECT

public:
    explicit GUIGameplay(QWidget *parent, GameGUI *game);

protected slots:

    /**
     * Override run_code in order to make it do an attempt to solve the level instead of a simple run.
     */
    void run_code() override;

    /**
     * Force the user to chose a filename (not directory, this is handled by the save mechanism)
     */
    void new_tab() override;

    /**
     * Just like GUISandbox::new_tab() except that it asks confirmation as it also delete the file.
     */
    void close_tab(int index) override;


private:
    QTextEdit *instruction_field;
    QTextEdit *vm_solution_output;
    QLabel *vm_solution_output_label;
    QMediaPlayer * level_w;
    QMediaPlayer * level_f;
    GameGUI *game;
    istringstream vm_input;

    void raw_gl_callback(GameLevel *gl);

    void raw_vm_solution_output_callback(int output);

    void send_typed_text_to_level();
};


#endif //A_STRESSFUL_MACHINE_GUIWINDOWGAMEPLAY_H
