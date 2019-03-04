#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "include/Ball.h"

int main(int argc, char *argv[  ])
{
    srand(time(NULL));


    initscr();
    curs_set(0);
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    Ball::initScene(yMax, xMax);

    Ball ball(10, 10, 1, 2, 2);

    for(int i = 0; i < INT32_MAX; i++)
    {
        ball.move();
        //ball.printLogs();
        clear();
        mvprintw(ball.getX(), ball.getY(), "o" );
        refresh();
        usleep(100000);
    }
    return 0;
} 