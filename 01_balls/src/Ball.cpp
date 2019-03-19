#include "../include/Ball.h"

int Ball::xMax;
int Ball::yMax;
bool Ball::runningFlag;

Ball::Ball()
{

}

Ball::Ball(int x, int y, int slow, int xDirection, int yDirection)
{
    this->x = x;
    this->y = y;
    this->slow = slow;
    this->xDirection = xDirection;
    this->yDirection = yDirection;
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

std::thread Ball::moveThread()
{
    return std::thread(&Ball::move, this);
}





