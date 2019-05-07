//
// Created by emile on 23/04/19.
//

#ifndef A_STRESSFUL_MACHINE_GUIFILEEDIT_H
#define A_STRESSFUL_MACHINE_GUIFILEEDIT_H


#include <QtWidgets/QTextEdit>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

/**
 * This class is derived from QTextEdit and add filename memory to it.
 */
class GUIFileEdit : public QTextEdit
{
public:

    fs::path file_path; /// The path of the file. Empty when the file was never saved.

    explicit GUIFileEdit(QWidget *parent = nullptr);

    explicit GUIFileEdit(fs::path file_path, QWidget *parent = nullptr);

    /**
     * Save the file if it was already saved
     * Else ask for a file path and the save it
     */
    void save();

    /**
     * Ask for a file path and save the file
     */
    void save_as();

    /**
     * Open a file at file_path
     * @warning Erase the current content of the widget
     * @param file_path The path of the file you want to open
     */
    void open(fs::path file_path);

    /**
     *
     * @return Whether this file was already saved once.
     */
    bool has_file_path();
};


#endif //A_STRESSFUL_MACHINE_GUIFILEEDIT_H
