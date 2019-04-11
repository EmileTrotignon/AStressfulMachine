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
#include "GUISandbox.h"

class GameGUI;

class GameLevel;

class GUIGameplay : public GUISandbox
{
    // Initialize macro for qt
    Q_OBJECT

public:
    explicit GUIGameplay(QWidget *parent, GameGUI *game);

protected slots:

    void run_code() override;

private:
    QTextEdit *instruction_field;
    QTextEdit *vm_solution_output;
    GameGUI *game;
    istringstream vm_input;

    void raw_gl_callback(GameLevel *gl);

    void raw_vm_solution_output_callback(int output);

    void send_typed_text_to_level();
};


#endif //A_STRESSFUL_MACHINE_GUIWINDOWGAMEPLAY_H
