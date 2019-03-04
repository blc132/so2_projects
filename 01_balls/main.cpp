#include <iostream>
#include <ncurses.h>


int main(int argc, char *argv[])
{
    initscr();
    WINDOW *win = newwin(15,15,1,1);

    box(win, '*', '*');
    touchwin(win);
    wrefresh(win);
    clear();

    getchar();

    endwin();
    return 0;
} 