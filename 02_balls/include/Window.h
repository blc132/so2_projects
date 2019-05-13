#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <vector>
#include "../include/Ball.h"

class Window
{
public:
    static int  wallLeftPadding;

    static int  getWallLeftPadding();
    static void  setWallLeftPadding(int value);

    int height;
    int width;
    int ballsOnLeftCounter;

    Window();
    ~Window();
    void renderScene(std::vector<Ball*> &balls);
    int getHeight();
    int getWidth();
private:
    bool running;

    void renderWall();
    void renderBalls(std::vector<Ball*> &balls);
};

#endif