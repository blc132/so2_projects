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

extern void printToFile(std::string data);

Window *window;
bool running = true;

void renderScene()
{
    while(running)
    {
        window->renderScene();
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

void printToFile(std::string data)
{
    std::ofstream myfile("logfile.txt", std::ios_base::app | std::ios_base::out);
    myfile <<  data + " " << std::endl;
    myfile.close();
}


int main(int argc, char *argv[  ])
{

    window = new Window();  
    std::thread renderSceneThread(renderScene);
    std::thread checkIfRunningThread(checkIfRunning);

    renderSceneThread.join();
    checkIfRunningThread.join();
    return 0;
}