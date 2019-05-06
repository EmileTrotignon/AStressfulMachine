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

    bool about_to_close;

    virtual void raw_vm_callback(VirtualMachine *vm);

    virtual void raw_vm_output_callback(int output);


    void run_code_prep();

    void run_code_finish();

private slots:

    void is_about_to_close();

protected slots:

    /**
     * @brief This slot runs the code the user typed
     */
    virtual void run_code();

    /**
     * @brief This slot closes an editor tab
     * @param index The index of the tab to close
     */
    virtual void close_tab(int index);

    /**
     * @brief This slot closes the current tab
     */
    virtual void close_current_tab();

    /**
     * @brief This slot opens a new tab.
     */
    virtual void new_tab();

    /**
     * @brief This slot save the current file, and other already saved once tabs
     * If the current tab was never saved, it asks the user for a path and a filename
     */
    virtual void save_file();

    /**
     * @brief This slot saves the current file and always ask for a path and filename
     */
    virtual void save_as_file();

    /**
     * @brief Open a file in a new tab
     */
    virtual void open_file();


};


#endif //A_STRESSFUL_MACHINE_GUISANDBOX_H
