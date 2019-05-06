//
// Created by marcel on 25/03/19.
//

#include <QtCore/QDir>
#include <QtWidgets/QtWidgets>
#include <QMediaPlayer>
#include <QSound>
#include <QFileInfo>
#include "GUIGameplay.h"
#include "GameGUI.h"
#include "GUIFileEdit.h"

void GUIGameplay::raw_gl_callback(GameLevel *gl)
{
    vm_input_field->clear();
    vm_input_field->insertPlainText(
            QString::fromStdString(gl->get_input_as_string()));
}

GUIGameplay::GUIGameplay(QWidget *parent, GameGUI *game_) : GUISandbox(game_->gamefiles_dir / "assets", parent),
                                                            game(game_), vm_input()
{
    instruction_field = new QTextEdit(this);
    instruction_field->insertPlainText(
            QString::fromStdString(game->game_sequence->get_current_level()->get_instructions()));

    vm_input_field->setReadOnly(true);
    vm_input_field->insertPlainText(
            QString::fromStdString(game->game_sequence->get_current_level()->get_input_as_string()));

    vm_solution_output = new QTextEdit(this);
    vm_solution_output->setReadOnly(true);

    vm_solution_output_label = new QLabel("Solution output", this);
    vm_solution_output_label->setFont(label_font);


    typing_tabs->removeTab(0);

    for (const auto &attempt_pair : game->game_sequence->get_current_level()->attempts)
    {
        auto text_edit = new GUIFileEdit(game->game_sequence->get_current_save_path() /
                                         game->game_sequence->get_current_level()->get_level_name() /
                                         attempt_pair.first,
                                         this);
        text_edit->setFont(field_font);
        //typing_zone_layout->addWidget(text_edit, 4);
        typing_tabs->addTab(text_edit, QString::fromStdString(attempt_pair.first));
    }
    typing_tabs->currentWidget()->setFocus();


    // Set fonts
    vm_input_field->setFont(field_font);
    instruction_field->setFont(field_font);

    // Add widgets to layout
    io_fields_layout->insertWidget(0, instruction_field);
    io_fields_layout->addWidget(vm_solution_output_label);
    io_fields_layout->addWidget(vm_solution_output);
}

void GUIGameplay::run_code()
{
    run_code_prep();


    auto game_song = new QMediaPlayer;
    // game_song->setMedia(QUrl::fromLocalFile("../data/assets/sounds/Start_game.wav"));
    game_song->setMedia(QUrl::fromLocalFile(QFileInfo("../data/assets/sounds/Start_game.wav").absoluteFilePath()));
	game_song->setVolume(50);
	game_song->play();

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
			level_w = new QMediaPlayer;
            // level_w->setMedia(QUrl::fromLocalFile("../data/assets/sounds/258142__tuudurt__level-win.wav"));
            level_w->setMedia(QUrl::fromLocalFile(QFileInfo(
                    QString::fromStdString((assets / "sounds/258142__tuudurt__level-win.wav").string())).absoluteFilePath()));
			level_w->setVolume(50);
			level_w->play();

            message_field->append("Congratulation, you solved this level");
            QMessageBox::StandardButton button = QMessageBox::critical(this, "Congrats",
                                                                       "Do you want to play another level ?",
                                                                       QMessageBox::Yes | QMessageBox::No,
                                                                       QMessageBox::Yes);
            if (button == QMessageBox::Yes)
            {
                ((GUIAdventureMode *) parent())->pick_level();
            }
        } else
        {
			level_f = new QMediaPlayer;
            // level_f->setMedia(QUrl::fromLocalFile("../data/assets/sounds/Level_failed.wav"));
            level_f->setMedia(QUrl::fromLocalFile(
                    QFileInfo(QString::fromStdString((assets / "sounds/Level_failed.wav").string())).absoluteFilePath()));
			level_f->setVolume(50);
			level_f->play();

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

void GUIGameplay::new_tab()
{
    auto text_edit = new GUIFileEdit(this);

    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty())
    {
        text_edit->setFont(field_font);
        text_edit->file_path = game->game_sequence->get_current_save_path() /
                               game->game_sequence->get_current_level()->get_level_name() / text.toStdString();
        typing_tabs->addTab(text_edit, text);
        typing_tabs->currentWidget()->setFocus();
    }

}

void GUIGameplay::close_tab(int index)
{
    QMessageBox::StandardButton b = QMessageBox::critical(this, "Confirm", "Do you really want to close this window ?",
                                                          QMessageBox::Close | QMessageBox::Cancel,
                                                          QMessageBox::Cancel);
    if (b == QMessageBox::Close)
    {
        fs::remove(((GUIFileEdit *) typing_tabs->widget(index))->file_path);
        GUISandbox::close_tab(index);
    }
}
