//
// Created by emile on 28/03/19.
//

#ifndef A_STRESSFUL_MACHINE_GUISANDBOX_H
#define A_STRESSFUL_MACHINE_GUISANDBOX_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QFont>
#include <QTextBrowser>
#include <QVBoxLayout>
#include "VirtualMachine.h"


class GUISandbox : public QWidget
{
    // Initialize macro for qt
Q_OBJECT

public:
    explicit GUISandbox(QWidget *parent = nullptr);

    friend void raw_vm_callback(VirtualMachine *vm, GUISandbox *sandbox);

private:

    QGridLayout *windowLayout;
    QVBoxLayout *io_fields_layout;
    QVBoxLayout *typing_zone_layout;
    QHBoxLayout *button_layout;

    QLabel *typing_field_label;
    QLabel *input_label;
    QLabel *output_label;
    QLabel *message_label;
    QLabel *memory_label;

    QTextEdit *typing_field;
    QTextEdit *vm_input_field;
    QTextEdit *vm_memory_printer;
    QTextEdit *vm_output;
    QTextEdit *message_field;

    QFont label_font;
    QFont field_font;

    QPushButton *run_button;
    QPushButton *next_operation_button;
    QPushButton *stop_button;
    QPushButton *pause_button;

private slots:

    void run_code();
};


#endif //A_STRESSFUL_MACHINE_GUISANDBOX_H
