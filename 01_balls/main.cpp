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
int ballsSlow = 100;
int ballsCreationTime = 5000;
int xMax, yMax;


void generateBalls()
{
    while(running)
    {
        getmaxyx(stdscr, yMax, xMax);
        Ball::setMaximumCords(xMax, yMax);
        directon ballDirection = static_cast<directon>(rand() % 8);
        balls.push_back(new Ball(xMax/2, yMax/2, ballsSlow, ballDirection));
        ballsThreads.push_back(balls.back()->moveThread());
        std::this_thread::sleep_for(std::chrono::milliseconds(ballsCreationTime));
    }
}

void renderScene()
{
    while(running)
    {
        clear();

        for(int i = 0; i < balls.size(); i++)
        {
            mvprintw(balls[i]->getY(), balls[i]->getX(), "o" );
        }

        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void terminateThreadsOfBalls()
{
    for (int i = 0; i < ballsThreads.size(); ++i)
    {
        ballsThreads[i].join();
    }
}

void checkIfRunning()
{
    while('x' != getch())
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    running = false;
}

int main(int argc, char *argv[  ])
{
    srand(time(NULL));
    initscr();
    curs_set(0);
    Ball::setRunningFlag(true);

    std::thread renderSceneThread(renderScene);
    std::thread generateBallsThread(generateBalls);
    std::thread checkIfRunningThread(checkIfRunning);

    renderSceneThread.join();
    generateBallsThread.join();
    terminateThreadsOfBalls();
    checkIfRunningThread.join();
    endwin();
    return 0;
}