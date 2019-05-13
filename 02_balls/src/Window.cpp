#include "../include/Window.h"
#include <vector>
#include <ncurses.h>

extern void printToFile(std::string data);

int Window::wallLeftPadding;

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

int Window::getWallLeftPadding()
{
    return wallLeftPadding;
}

void Window::setWallLeftPadding(int value)
{
    wallLeftPadding = value;
}
#pragma endregion

void Window::renderScene(std::vector<Ball*> &balls)
{
    clear();
    renderWall();
    renderBalls(balls);

    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}


void Window::renderWall()
{
    for(int i = 0; i < width; i++)
    {
        mvprintw(i, wallLeftPadding, "|" );
    } 
}


void Window::renderBalls(std::vector<Ball*> &balls)
{
    for(int i = 0; i < balls.size(); i++)
    {
        mvprintw(balls[i]->getY(), balls[i]->getX(), "o" );
    }
}