//
// Created by marcel on 25/03/19.
//

#include "GUIGameplay.h"
#include "GameGUI.h"

void GUIGameplay::raw_gl_callback(GameLevel *gl)
{
    vm_input_field->clear();
    vm_input_field->insertPlainText(
            QString::fromStdString(gl->get_input_as_string()));
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

    typing_tabs->removeTab(0);

    for (const auto &attempt_pair : game->game_sequence->get_current_level()->attempts)
    {
        auto text_edit = new QTextEdit(this);
        text_edit->setFont(field_font);
        text_edit->insertPlainText(QString::fromStdString(attempt_pair.second));
        //typing_zone_layout->addWidget(text_edit, 4);
        typing_tabs->addTab(text_edit, QString::fromStdString(attempt_pair.first));
    }
    typing_tabs->currentWidget()->setFocus();


    // Set fonts
    vm_input_field->setFont(field_font);
    instruction_field->setFont(field_font);

    // Add widgets to layout
    io_fields_layout->addWidget(instruction_field);
    io_fields_layout->addWidget(vm_solution_output);
}

void GUIGameplay::run_code()
{
    run_code_prep();

    using namespace placeholders;
    function<void(GameLevel *)> gl_callback = bind(&GUIGameplay::raw_gl_callback, this, _1);
    function<void(VirtualMachine *)> vm_callback = bind(&GUIGameplay::raw_vm_callback, this, _1);
    function<void(int)> vm_output_callback = bind(&GUIGameplay::raw_vm_output_callback, this, _1);
    function<void(int)> vm_solution_callback = bind(&GUIGameplay::raw_vm_solution_output_callback, this, _1);

    try
    {
        bool b = game->game_sequence->get_current_level()->attempt(
                ((QTextEdit *) typing_tabs->currentWidget())->toPlainText().toStdString(),
                vm_callback,
                gl_callback,
                vm_output_callback,
                vm_solution_callback);
        if (b)
        {
            message_field->append("Congratulation, you solved this level");
        } else
        {
            message_field->append("Your output differs from the expected output, try again :(");
        }
    } catch (const VirtualMachineException &e)
    {
        message_field->append(QString("Error : ") + e.what());

    }

    run_code_finish();

    ((QTextEdit *) typing_tabs->currentWidget())->insertPlainText(
            QString::fromStdString(game->game_sequence->get_current_level()->current_attempt->second));
}


void GUIGameplay::raw_vm_solution_output_callback(int output)
{
    vm_solution_output->append(QString::number(output));

}

void GUIGameplay::send_typed_text_to_level()
{
    for (int i = 0; i < typing_tabs->count(); i++)
    {
        game->game_sequence->get_current_level()->attempts[typing_tabs->tabText(i).toStdString()] =
                ((QTextEdit *) typing_tabs->widget(i))->toPlainText().toStdString();
    }
}
