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
    int height;
    int width;
    int wallLeftPadding = 40;

    Window();
    ~Window();
    void renderScene(std::vector<Ball*> &balls);
    int getHeight();
    int getWidth();
    int getWallLeftPadding();
private:
    bool running;

    void renderWall();
    void renderBalls(std::vector<Ball*> &balls);
};

#endif