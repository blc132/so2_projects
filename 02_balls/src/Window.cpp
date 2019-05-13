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

void Window::renderBalls(std::vector<Ball*> &balls)
{
        clear();

        for(int i = 0; i < balls.size(); i++)
        {
            mvprintw(balls[i]->getY(), balls[i]->getX(), "o" );
        }

        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

int Window::getHeight()
{
    return height;
}

int Window::getWidth()
{
    return width;
}