#include "../include/Window.h"
#include <vector>
#include <ncurses.h>

Window::Window()
{
    initscr();
    noecho();
    curs_set(FALSE);
    clear();
    refresh(); 
    getmaxyx(stdscr, height, width);   

}

Window::~Window()
{
    endwin();
}

#pragma region GETTERS_SETTERS
int Window::getHeight()
{
    return this->height;
}

int Window::getWidth()
{
    return this->width;
}
#pragma endregion

void Window::renderScene()
{
    clear();

    //renderwanko tutaj

    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}