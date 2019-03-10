#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <random>

#include "include/Ball.h"

std::vector<Ball> balls;
bool running = true;
int xMax, yMax;


void checkIfRunning()
{
    while('x' != getchar());
    running = false;
}

void generateBalls()
{
    while(running)
    {
        Ball ball(yMax/2, xMax/2, 120000, (rand() % 3), (rand() % 3));
        std::thread ballThread = ball.moveThread();
        balls.push_back(ball);
        usleep(1000000);
    }
}

int main(int argc, char *argv[  ])
{
    srand(time(NULL));
    initscr();
    curs_set(0);
    getmaxyx(stdscr, yMax, xMax);
    Ball::drawScene(yMax, xMax);

    Ball ball(yMax/2, xMax/2, 120000, (rand() % 3), (rand() % 3));
    balls.push_back(ball);
    std::cout<<std::to_string(xMax/2)<<" "<<std::to_string(yMax/2)<<std::endl;
    std::cout<<std::to_string(ball.getX())<<" "<<std::to_string(ball.getY())<<std::endl;

    std::thread runningThread(checkIfRunning);
    std::thread generateBallsThread(generateBalls);

    while(running)
    {

        for(int i = 0; i < balls.size(); i++)
        {
            balls[i].move();
            //ball.printLogs();
            mvprintw(balls[i].getPreviousX(), balls[i].getPreviousY(), " " );
            mvprintw(balls[i].getX(), balls[i].getY(), "o" );
            usleep(balls[i].getSlow());
            refresh();

        }

    }

    runningThread.join();
    endwin();
    return 0;
}