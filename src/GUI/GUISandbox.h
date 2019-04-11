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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QPixmap>
#include <QIcon>

#include "VirtualMachine.h"


class GUISandbox : public QWidget
{
    // Initialize macro for qt
Q_OBJECT

public:
    explicit GUISandbox(QWidget *parent = nullptr);

protected:

    virtual void place_widgets_on_layout();

    static const int max_speed = 10;

    QMenuBar *menu_bar;

    QGridLayout *windowLayout;
    QVBoxLayout *io_fields_layout;
    QTabWidget *typing_tabs;
    QVBoxLayout *typing_zone_layout;
    QHBoxLayout *button_layout;

    QLabel *typing_field_label;
    QLabel *input_label;
    QLabel *output_label;
    QLabel *message_label;
    QLabel *memory_label;


    //QTextEdit *typing_field;
    QTextEdit *vm_input_field;
    QTextEdit *vm_memory_printer;
    QTextEdit *vm_output;
    QTextEdit *message_field;

    QFont label_font;
    QFont field_font;

    QPushButton *run_button;
    QPushButton *next_operation_button;
    QPushButton *stop_button;

    QSlider *speed_slider;

    virtual void raw_vm_callback(VirtualMachine *vm);

    virtual void raw_vm_output_callback(int output);

    void run_code_prep();

    void run_code_finish();

protected slots:

    virtual void run_code();

};


#endif //A_STRESSFUL_MACHINE_GUISANDBOX_H
