#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <random>
#include <chrono>
#include <vector>
#include <fstream>
#include "include/Window.h"
#include "include/ShopCounter.h"
#include "include/Data.h"

extern void printToFile(std::string data);

Window *window;
ShopCounter *shopCounter;
std::vector<std::thread> generatingThreads;

bool running = true;


void renderScene()
{
    while(running)
    {
        window->renderScene();
    }
}

void generateResources()
{
    generatingThreads.push_back(shopCounter->generateEggsThread());
    generatingThreads.push_back(shopCounter->generateMeatsThread());
    generatingThreads.push_back(shopCounter->generateRollsThread());
}

void checkIfRunning()
{
    cbreak();
    noecho();
    while('x' != getch())
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    running = false;
}

void printToFile(std::string data)
{
    std::ofstream myfile("logfile.txt", std::ios_base::app | std::ios_base::out);
    myfile <<  data + " " << std::endl;
    myfile.close();
}


int main(int argc, char *argv[  ])
{
    window = new Window();  
    shopCounter = new ShopCounter();

    std::thread generateResourcesThread(generateResources);
    std::thread renderSceneThread(renderScene);
    std::thread checkIfRunningThread(checkIfRunning);

    renderSceneThread.join();
    checkIfRunningThread.join();
    generateResourcesThread.join();
    return 0;
}