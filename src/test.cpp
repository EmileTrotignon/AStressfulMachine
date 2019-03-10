//
// Created by emile on 10/03/19.
//
#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <assert.h>

#include "ncurses_utilities.h"

bool test_ncurses_utilities()
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    vector<string> options = {"option1", "option2", "option3"};
    int c = menu(options, stdscr);
    endwin();
    cout << "The option you chose was : Option" << c + 1 << " ? [Y/n]" << endl;
    char b;
    cin >> b;
    return (b == 'y' || b == 'Y');

}

int main()
{
    assert(test_ncurses_utilities());

    cout << "tests passed" << endl;
    return 0;
}