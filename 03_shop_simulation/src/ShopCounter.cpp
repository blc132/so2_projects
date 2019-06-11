#include "../include/ShopCounter.h"

extern int eggsCounter = 3;
extern int rollsCounter = 2;
extern int meatsCounter = 5;
extern bool running;
extern int eggsGenerationTime = 500;
extern int rollsGenerationTime = 300;
extern int meatsGenerationTime = 200;

ShopCounter::ShopCounter()
{
}

ShopCounter::~ShopCounter()
{
}

void ShopCounter::generateEggs()
{
    while (running)
    {
        eggsCounter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(eggsGenerationTime));
    }
}

void ShopCounter::generateRolls()
{
    while (running)
    {
        rollsCounter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(rollsGenerationTime));
    }
}

void ShopCounter::generateMeats()
{
    while (running)
    {
        meatsCounter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(meatsGenerationTime));
    }
}

std::thread ShopCounter::generateEggsThread()
{
    return std::thread(&ShopCounter::generateEggs, this);
}

std::thread ShopCounter::generateRollsThread()
{
    return std::thread(&ShopCounter::generateRolls, this);
}

std::thread ShopCounter::generateMeatsThread()
{
    return std::thread(&ShopCounter::generateMeats, this);
}