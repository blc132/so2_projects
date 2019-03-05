#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <random>

#include "include/Ball.h"

std::vector<Ball> balls;
bool running = true;

void refreshScreen()
{
    while(running == true)
    {
        clear();

        for(int i = 0; i < balls.size(); i++)
        {
            mvprintw(balls[i].getX(), balls[i].getY(), "o" );
        }

        refresh();
        usleep(10000);   
    }
}

int main(int argc, char *argv[  ])
{
    srand(time(NULL));
    int xMax, yMax;
    std::vector<std::thread> ballsThreads;

    initscr();
    curs_set(0);
    getmaxyx(stdscr, yMax, xMax);
    Ball::initScene(yMax, xMax);

    Ball ball(yMax/2, xMax/2, 3, (rand() % 3), (rand() % 3));
    balls.push_back(ball);
    std::cout<<std::to_string(xMax/2)<<" "<<std::to_string(yMax/2)<<std::endl;
    std::cout<<std::to_string(ball.getX())<<" "<<std::to_string(ball.getY())<<std::endl;
    for(int i = 0; i < INT32_MAX; i++)
    {
        balls[i].move();
        //ball.printLogs();
        clear();
        mvprintw(balls[i].getX(), balls[i].getY(), "o" );
        refresh();
        usleep(100000);
    }
    return 0;
} 