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
        // checkIfBallIsOnLeft(balls[i]);
        mvprintw(balls[i]->getY(), balls[i]->getX(), "o" );
    }
}

// void Window::checkIfBallIsOnLeft(Ball* ball)
// {
//     if(ball->getX() <= wallLeftPadding)
//     {
//         if(ball->getInLeftArea() == false)
//         {
//             ball->setInLeftArea(true);
//             Ball::setBallsInLeftArea(Ball::getBallsInLeftArea() + 1);
//             printToFile(std::to_string(Ball::getBallsInLeftArea() ));
//         }
//     }
//     else
//     {
//         if(ball->getInLeftArea() == true)
//         {
//             ball->setInLeftArea(false);  
//             Ball::setBallsInLeftArea(Ball::getBallsInLeftArea() - 1);   
//             printToFile(std::to_string(Ball::getBallsInLeftArea()));
//         }
//     }
// }