#include "../include/Ball.h"

int Ball::xMax;
int Ball::yMax;

Ball::Ball()
{

}

Ball::Ball(int x, int y, int speed, int xDirection, int yDirection)
{
    this->x = x;
    this->y = y;
    this->speed = speed;
    this->xDirection = xDirection;
    this->yDirection = yDirection;
}

Ball::~Ball()
{

}

void Ball::initScene(int windowX, int windowY)
{
    xMax = windowX;
    yMax = windowY;
}

int Ball::getX()
{
    return this->x;
}

int Ball::getY()
{
    return this->y;
}


void Ball::move()
{
    if(this->x >= xMax || this->x <= 0)
    {
        xDirection = -xDirection;
    }
    if(this->y >= yMax || this->y <= 0)
    {
        yDirection = -yDirection;
    }
    
    x += xDirection;
    y += yDirection;
}

void Ball::printLogs()
{
    std::cout<<"x: "<<std::to_string(x)<<" y: "<<std::to_string(y)<<std::endl;
    std::cout<<"xDirection: "<<std::to_string(xDirection)<<" yDirection: "<<std::to_string(yDirection)<<std::endl;
}



