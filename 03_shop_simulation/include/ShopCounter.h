#ifndef SHOPCOUNTER_H
#define SHOPCOUNTER_H

#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <vector>
#include <mutex>

#include "Data.h"

class ShopCounter
{
public:

    ShopCounter();
    ~ShopCounter();

    std::thread generateEggsThread();
    std::thread generateRollsThread();
    std::thread generateMeatsThread();
private:
    void generateEggs();
    void generateRolls();
    void generateMeats();
};

#endif