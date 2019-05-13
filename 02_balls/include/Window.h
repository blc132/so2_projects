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

    Window();
    ~Window();
    void renderBalls(std::vector<Ball*> &balls);
    int getHeight();
    int getWidth();
private:
    bool running;
};

#endif