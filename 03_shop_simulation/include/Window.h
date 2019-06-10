#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <vector>

class Window
{
public:
    int height;
    int width;

    Window();
    ~Window();
    void renderScene();
    int getHeight();
    int getWidth();
private:
    bool running;
};

#endif