#include "../include/ShopCounter.h"

extern int eggsCounter = 0;
extern int rollsCounter = 0;
extern int meatsCounter = 0;
extern bool running;
extern int eggsGenerationTime = 5000;
extern int rollsGenerationTime = 3000;
extern int meatsGenerationTime = 2000;

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