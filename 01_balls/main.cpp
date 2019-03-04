#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "include/Ball.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    Ball::initScene(400, 400);

    Ball ball(10, 10, 2.0, static_cast<directon>(rand() % 4));
    // initscr();
    // WINDOW *win = newwin(15,15,1,1);

    // box(win, '*', '*');
    // touchwin(win);
    // wrefresh(win);
    // clear();

    // getchar();

    // endwin();
    return 0;
} 