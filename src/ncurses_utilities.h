//
// Created by emile on 10/03/19.
//

#ifndef A_STRESSFUL_MACHINE_NCURSES_UTILITIES_H
#define A_STRESSFUL_MACHINE_NCURSES_UTILITIES_H

#include <ncurses.h>
#include <iostream>
#include <vector>
#include "VirtualMachine.h"

using namespace std;

int menu(const vector<string> &options, WINDOW *win);

WINDOW *create_newwin(int height, int width, int starty, int startx);

void destroy_win(WINDOW *local_win);

void print_program_to_win(WINDOW *win, VirtualMachine *vm);

void print_memory_to_win(WINDOW *win, VirtualMachine *vm);

#endif //A_STRESSFUL_MACHINE_NCURSES_UTILITIES_H
