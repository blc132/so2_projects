#include "../include/Ball.h"
#include "../include/Window.h"

extern void printToFile(std::string data);

int Ball::xMax;
int Ball::yMax;
int Ball::ballsInLeftArea;
int Ball::maxNumberOfBallsInLeftArea;
bool Ball::runningFlag;

#pragma region CONSTRUCTORS_DESTRUCTORS

Ball::Ball()
{

}

Ball::Ball(int x, int y, speed ballSpeed, directon ballDirection, int id)
{
    this->x = x;
    this->y = y;
    this->id = id;
    setDirection(ballDirection);
    setSpeed(ballSpeed);
}

Ball::~Ball()
{

}
#pragma endregion

#pragma region GETTERS_SETTERS
void Ball::setMaximumCords(int windowX, int windowY)
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

int Ball::getBallsInLeftArea()
{
    return ballsInLeftArea;
}

void Ball::setBallsInLeftArea(int value)
{
    ballsInLeftArea = value;
}

int Ball::getMaxNumberOfBallsInLeftArea()
{
    return maxNumberOfBallsInLeftArea;
}

void Ball::setMaxNumberOfBallsInLeftArea(int value)
{
    maxNumberOfBallsInLeftArea = value;
}

int Ball::getX()
{
    return this->x;
}

int Ball::getY()
{
    return this->y;
}

bool Ball::getInLeftArea()
{
    return this->inLeftArea;
}

void Ball::setInLeftArea(bool value)
{
    this->inLeftArea = value;
}

int Ball::getId()
{
    return this->id;
}
#pragma endregion

void Ball::move()
{
    while(runningFlag) {

        checkLeftAreaMutex.lock();
        this->checkIfIsInLeftArea();
        checkLeftAreaMutex.unlock();        
        
        bool canMove = !(ballsInLeftArea >= maxNumberOfBallsInLeftArea && !this->inLeftArea && this->x == Window::getWallLeftPadding());
        // printToFile("pilka nr: " + std::to_string(this->id));
        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        if(canMove)
        {
           if (this->x >= xMax  || this->x <= 0) {
            xDirection = -xDirection;
            }

            if (this->y >= yMax || this->y <= 0) {
                yDirection = -yDirection;
            }

            y += yDirection;
            x += xDirection;         
        }                      
        std::this_thread::sleep_for(std::chrono::milliseconds(slowdown));
    }
}


void Ball::printLogs()
{
    std::cout<<"x: "<<std::to_string(x)<<" y: "<<std::to_string(y)<<std::endl;
    std::cout<<"xDirection: "<<std::to_string(xDirection)<<" yDirection: "<<std::to_string(yDirection)<<std::endl;
}

void Ball::setDirection(directon ballDirection) 
{

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

void Ball::setSpeed(speed ballSpeed)
{
    switch (ballSpeed)
    {
        case slow:
            slowdown = 200;
            break;

        case medium:
            slowdown = 100;
            break;

        case fast:
            slowdown = 50;
            break;

        default:
            slowdown = 100;

    }
}

void Ball::checkIfIsInLeftArea()
{
    if(x < Window::getWallLeftPadding())
    {
        if(!inLeftArea && ballsInLeftArea < maxNumberOfBallsInLeftArea)
        {
            inLeftArea = true;
            ballsInLeftArea++;
            printToFile(std::to_string(ballsInLeftArea));
        }
    }
    else
    {
        if(inLeftArea)
        {
            inLeftArea = false; 
            ballsInLeftArea--;
            printToFile(std::to_string(ballsInLeftArea));
        }
    }
}


std::thread Ball::moveThread()
{
    return std::thread(&Ball::move, this);
}
