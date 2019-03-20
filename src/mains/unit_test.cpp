//
// Created by emile on 10/03/19.
//
#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cassert>
#include "VirtualMachine.h"


#include "ncurses++.h"

class UnitTest {
public:
    static bool test_OCursedStream()
    {
        using namespace ncursespp;
        initscr_();
        noecho();
        Window lol = Window(stdscr_->get_height(), stdscr_->get_width(), 0, 0);
        OCursedStream lols = OCursedStream(&lol, 3, 3);
        lols << "qwertyuiop";
        lols << 'a';
        lols.flush();
        lol.getch_();
        // while (true) lol.getch_();

        endwin_();
        return true;
    }

    static void test_virtualMachine() {

        cout << "Beginning test of virtualMachine class" << endl;

        //
        stringstream entree;
        ostringstream sortie;

        // Test class with empty program
        string testProgramValOp = "+.-.+++.----."; // Test VAL_INCR & VAL_DINCR
        string testProgramPtrOp = ".>+.>++.>>>--.<<<<."; // Test PTR_INCR & PTR_DINCR

        // Testing with an empty program
        string testProgramEmpty;
        VirtualMachine testObject1(testProgramEmpty, &entree, &sortie);
        assert(testObject1.program == "");
        assert(testObject1.get_status() == STATUS_PAUSED);
        // assert( (*get_current_operator()) ==  ) With iterator check empty? begin() == end()
        // assert(testObject1.get_memory())
        // assert(testObject1.get_memory_ptr())

        entree << 25;
        string testProgramStreamOp = ",."; // Test VAL_OUT & VAL_IN
        VirtualMachine testObject2(testProgramStreamOp, &entree, &sortie);
        assert(testObject2.get_program() == testProgramStreamOp);
        testObject2.do_one_iteration(true);
        // assert(testObject2.memory[0] == 25);
        testObject2.do_one_iteration(true);
        // assert(sortie.str() == "25");




        cout << "Test of virtualMachine class successfully finished" << endl;
    }

};


int main()
{
    cout << "Would you like to test OCursedStream class? (y/n) This will open a ncurses window" << endl;
    char answer;
    cin >> answer;
    if (answer == 'y' || answer == 'Y') assert(UnitTest::test_OCursedStream());
    UnitTest::test_virtualMachine();

    cout << "All tests successfully passed" << endl;
    return 0;
}