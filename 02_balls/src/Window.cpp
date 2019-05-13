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

int Window::getHeight()
{
    return height;
}

int Window::getWidth()
{
    return width;
}

int Window::getWallLeftPadding()
{
    return wallLeftPadding;
}

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