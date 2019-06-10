#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include "include/Window.h"

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


int main(int argc, char *argv[  ])
{

    window = new Window();  
    std::thread renderSceneThread(renderScene);
    std::thread checkIfRunningThread(checkIfRunning);
    
    renderSceneThread.join();
    checkIfRunningThread.join();
    return 0;
}