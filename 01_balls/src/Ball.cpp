#include "../include/Ball.h"

int Ball::xMax;
int Ball::yMax;
bool Ball::runningFlag;

Ball::Ball()
{

}

Ball::Ball(int x, int y, int slow, directon ballDirection)
{
    this->x = x;
    this->y = y;
    this->slow = slow;
    setDirection(ballDirection);
}

Ball::~Ball()
{

}

void Ball::drawScene(int windowX, int windowY)
{
    xMax = windowX;
    yMax = windowY;
}


bool Ball::getRunningFlag()
{
    return runningFlag;
}

void Ball::setRunningFlag(bool flag)
{
    runningFlag = flag;
}

int Ball::getX()
{
    return this->x;
}

int Ball::getY()
{
    return this->y;
}

int Ball::getSlow()
{
    return this->slow;
}

void Ball::move()
{
    while(runningFlag) {
        if (this->x >= xMax  || this->x <= 0) {
            xDirection = -xDirection;
        }
        if (this->y >= yMax || this->y <= 0) {
            yDirection = -yDirection;
        }
//        previousX = x;
//        previousY = y;
//        std::cout<<"x: "<<std::to_string(x)<<" y: "<<std::to_string(y)<<std::endl;
//        std::cout<<"xDirection: "<<std::to_string(xDirection)<<" yDirection: "<<std::to_string(yDirection)<<std::endl;
        y += yDirection;
        x += xDirection;
//        std::cout<<"x: "<<std::to_string(x)<<" y: "<<std::to_string(y)<<std::endl;
//        std::cout<<"xDirection: "<<std::to_string(xDirection)<<" yDirection: "<<std::to_string(yDirection)<<std::endl;
//        std::cout<<"x: "<<std::to_string(x)<<" y: "<<std::to_string(y)<<std::endl;
//        std::cout<<"test"<<std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(slow));
    }
}


void Ball::printLogs()
{
    std::cout<<"x: "<<std::to_string(x)<<" y: "<<std::to_string(y)<<std::endl;
    std::cout<<"xDirection: "<<std::to_string(xDirection)<<" yDirection: "<<std::to_string(yDirection)<<std::endl;
}

void Ball::setDirection(directon ballDirection) {
    switch (ballDirection)
    {
        case up:
            xDirection = 0;
            yDirection = -1;
            break;

        case left:
            xDirection = -1;
            yDirection = 0;
            break;

        case down:
            xDirection = 0;
            yDirection = 1;
            break;

        case right:
            xDirection = 1;
            yDirection = 0;
            break;

        case up_left:
            xDirection = -1;
            yDirection = -1;
            break;

        case up_right:
            xDirection = 1;
            yDirection = -1;
            break;

        case down_left:
            xDirection = -1;
            yDirection = 1;
            break;

        case down_right:
            xDirection = 1;
            yDirection = 1;
            break;

        default:
            xDirection = 0;
            yDirection = 0;

    }
}

std::thread Ball::moveThread()
{
    return std::thread(&Ball::move, this);
}






