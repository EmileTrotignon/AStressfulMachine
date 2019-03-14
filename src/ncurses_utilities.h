//
// Created by emile on 10/03/19.
//

#ifndef A_STRESSFUL_MACHINE_NCURSES_UTILITIES_H
#define A_STRESSFUL_MACHINE_NCURSES_UTILITIES_H

#include <ncurses.h>
#include <iostream>
#include <vector>
#include "VirtualMachine.h"
#include "GameLevel.h"

using namespace std;

class NcursesWindow;

int menu(const vector<string> &options, WINDOW *win);

WINDOW *create_newwin(int height, int width, int starty, int startx);

void sbox(WINDOW *win);

void destroy_win(WINDOW *local_win);

void mvwprintstr(WINDOW *win, int y, int x, string str);

void print_program_to_win(NcursesWindow *win, VirtualMachine *vm);

void print_memory_to_win(NcursesWindow *win, VirtualMachine *vm);

void print_input_to_win(NcursesWindow *win, GameLevel *gl);

#endif //A_STRESSFUL_MACHINE_NCURSES_UTILITIES_H
