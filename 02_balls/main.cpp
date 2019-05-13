#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <random>
#include <chrono>
#include <vector>
#include <fstream>

#include "include/Ball.h"
#include "include/Window.h"

std::vector<Ball*> balls;
std::vector<std::thread> ballsThreads;
static bool running = true;
int ballsCreationTime = 1000;
Window *window;

void printToFile(std::string data)
{
    std::ofstream myfile("logfile.txt", std::ios_base::app | std::ios_base::out);
    myfile <<  data + " " << std::endl;
    myfile.close();
}

void generateBalls()
{
    Ball::setMaximumCords(window->getWidth(), window->getHeight());
    while(running)
    {
        // printToFile(std::to_string(window->getWidth()));
        // printToFile(std::to_string(window->getHeight()));

        directon ballDirection = static_cast<directon>(rand() % 8);
        speed ballSpeed = static_cast<speed>(rand() % 2);
        balls.push_back(new Ball(window->getWidth()/2, window->getHeight()/2, ballSpeed, ballDirection));
        ballsThreads.push_back(balls.back()->moveThread());
        std::this_thread::sleep_for(std::chrono::milliseconds(ballsCreationTime));
    }
}

void renderScene()
{
    while(running)
    {
        window->renderScene(balls);
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
    cbreak();
    noecho();
    while('x' != getch())
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    running = false;
}

int main(int argc, char *argv[  ])
{
    srand(time(NULL));
    Ball::setRunningFlag(true);
    
    window = new Window();  
    Window::setWallLeftPadding(40);

    std::thread renderSceneThread(renderScene);
    std::thread generateBallsThread(generateBalls);
    std::thread checkIfRunningThread(checkIfRunning);

    renderSceneThread.join();
    generateBallsThread.join();
    terminateThreadsOfBalls();
    checkIfRunningThread.join();

    return 0;
}