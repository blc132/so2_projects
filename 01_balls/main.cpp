#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <random>
#include <chrono>
#include <vector>

#include "include/Ball.h"

std::vector<Ball*> balls;
std::vector<std::thread> ballsThreads;
static bool running = true;
int slow = 100;
int xMax, yMax;


void generateBalls()
{
    while(running)
    {
        balls.push_back(new Ball(yMax/2, xMax/2, slow, (rand() % 3) - 1, (rand() % 3) - 1));
        ballsThreads.push_back(balls.back()->moveThread());
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void renderScene()
{
    while(running)
    {
        clear();

        for(int i = 0; i < balls.size(); i++)
        {
//            std::cout<<"plika nr: "<<std::to_string(i)<<std::endl;
//                balls[i].printLogs();
//                std::cout<<"plika nr: "<<std::to_string(i)<<std::endl;
            mvprintw(balls[i]->getX(), balls[i]->getY(), "o" );

        }
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));


    }
}

void checkIfRunning()
{
    while('x' != getch())
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));;
    running = false;
}

int main(int argc, char *argv[  ])
{
    srand(time(NULL));
    initscr();
    curs_set(0);
    getmaxyx(stdscr, yMax, xMax);
//    xMax = 200;
//    yMax = 200;
    Ball::drawScene(yMax, yMax);
    Ball::setRunningFlag(true);

    std::thread generateBallsThread(generateBalls);
    std::thread renderSceneThread(renderScene);
    std::thread checkIfRunningThread(checkIfRunning);

    while(running)  { std::this_thread::sleep_for(std::chrono::milliseconds(500)); }

    endwin();
    return 0;
}