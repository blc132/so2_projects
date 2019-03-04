#include "../include/Ball.h"

int Ball::xMax;
int Ball::yMax;

Ball::Ball()
{

}

Ball::Ball(int x, int y, float speed, directon dir)
{
    this->x = x;
    this->y = y;
    this->speed = speed;
    this->dir = dir;
}

Ball::~Ball()
{

}

void Ball::initScene(int windowX, int windowY)
{
    xMax = windowX;
    yMax = windowY;
}



