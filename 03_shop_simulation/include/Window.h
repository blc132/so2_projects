#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <vector>
#include <mutex>

#include "Data.h"

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

    void renderShopCounter();
    void renderShopQueue();
    void renderShopCashBox(int x, int y, short colorNumber, short cashNumber);
    void renderFrontDoors();
    void renderCustomers();
};

#endif