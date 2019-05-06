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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>

#include "VirtualMachine.h"


class GUISandbox : public QWidget
{
    // Initialize macro for qt
Q_OBJECT

private:

    void place_widgets_on_layout();

    void fill_menu_bar();

public:
    explicit GUISandbox(fs::path assets, QWidget *parent = nullptr);

    ~GUISandbox() override;

protected:

    static const int max_speed = 10;

    const fs::path assets;

    QMenuBar *menu_bar;

    QMenu *file_menu;
    QAction *new_tab_action;
    QAction *save_file_action;
    QAction *save_as_file_action;
    QAction *open_file_action;

    QHBoxLayout *window_layout;
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

    virtual void close_tab(int index);

    virtual void close_current_tab();

    virtual void new_tab();

    virtual void save_file();

    virtual void save_as_file();

    virtual void open_file();


};


#endif //A_STRESSFUL_MACHINE_GUISANDBOX_H
