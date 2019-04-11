//
// Created by marcel on 25/03/19.
//

#include "GUIGameplay.h"
#include "GameGUI.h"

void GUIGameplay::raw_gl_callback(GameLevel *gl)
{
    vm_input_field->clear();
    vm_input_field->insertPlainText(
            QString::fromStdString(game->game_sequence->get_current_level()->get_input_as_string()));
}

GUIGameplay::GUIGameplay(QWidget *parent, GameGUI *game_) : GUISandbox(parent), game(game_), vm_input()
{
    instruction_field = new QTextEdit(this);
    instruction_field->insertPlainText(
            QString::fromStdString(game->game_sequence->get_current_level()->get_instructions()));

    vm_input_field->setReadOnly(true);
    vm_input_field->insertPlainText(
            QString::fromStdString(game->game_sequence->get_current_level()->get_input_as_string()));

    vm_solution_output = new QTextEdit(this);

    // Set fonts
    vm_input_field->setFont(field_font);
    instruction_field->setFont(field_font);

    io_fields_layout->addWidget(instruction_field);
    io_fields_layout->addWidget(vm_solution_output);
}

void GUIGameplay::run_code()
{
    using namespace placeholders;
    function<void(GameLevel *)> gl_callback = bind(&GUIGameplay::raw_gl_callback, this, _1);
    function<void(VirtualMachine *)> vm_callback = bind(&GUIGameplay::raw_vm_callback, this, _1);
    function<void(int)> vm_output_callback = bind(&GUIGameplay::raw_vm_output_callback, this, _1);
    function<void(int)> vm_solution_callback = bind(&GUIGameplay::raw_vm_solution_output_callback, this, _1);

    game->game_sequence->get_current_level()->attempt(
            ((QTextEdit *) typing_tabs->currentWidget())->toPlainText().toStdString(),
            vm_callback,
            gl_callback,
            vm_output_callback,
            vm_solution_callback);
}

void GUIGameplay::raw_vm_solution_output_callback(int output)
{
    vm_solution_output->append(QString::number(output));

}
