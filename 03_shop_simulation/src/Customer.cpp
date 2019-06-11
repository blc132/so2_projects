#include "../include/Customer.h"

extern void printToFile(std::string data);

extern bool running;
extern int eggsCounter;
extern int rollsCounter;
extern int meatsCounter;

std::mutex shopCounterMutex;
std::mutex getResourcesMutex;
std::mutex shopQueueMutex;
std::condition_variable cv;

Customer::Customer()
{
}

Customer::~Customer()
{
}

Customer::Customer(int x, int y, int customSpeed, int needOfEggs, int needOfRolls, int needOfMeats, short color)
{
    this->x = x;
    this->y = y;
    this->needOfEggs = needOfEggs;
    this->needOfRolls = needOfRolls;
    this->needOfMeats = needOfMeats;
    this->customSpeed = customSpeed;
    this->color = color;
}

void Customer::move()
{
    while (running)
    {
        goToShopCounter();
        std::this_thread::sleep_for(std::chrono::milliseconds(pauseBetweenMoves));

        interactionWithShopCounter();

        this->hasShopping = true;
        goToShopQueue();
        std::this_thread::sleep_for(std::chrono::milliseconds(pauseBetweenMoves));
        goToShopCashBox(rand() % 3 + 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(pauseBetweenMoves));
        this->hasShopping = false;
        goToFrontDoors();
        std::this_thread::sleep_for(std::chrono::milliseconds(pauseBetweenMoves));
    }
    //podejdź do lady
    //czekaj
    //weź to co chcesz
    //idz do kolejki do kasy
    //czekaj
    //wybierz jedną z kas
}

void Customer::interactionWithShopCounter()
{
    bool shopHasAllProducts = false;
    while (!shopHasAllProducts)
    {
        std::unique_lock<std::mutex> lock(shopCounterMutex);
        printToFile("shopCounterMutex, gracz nr: " + std::to_string(color));
        shopHasAllProducts = (needOfEggs <= eggsCounter && needOfMeats <= meatsCounter && needOfRolls <= rollsCounter);    

        if (shopHasAllProducts)
        {
            // std::unique_lock<std::mutex> lock(getResourcesMutex);
            eggsCounter -= needOfEggs;
            rollsCounter -= needOfRolls;
            meatsCounter -= needOfMeats;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        lock.unlock(); 
    }

    // std::unique_lock<std::mutex> lock(checkLeftAreaMutex);
    // // printToFile("Zablokowany przez: " + std::to_string(id));
    // this->checkIfIsInLeftArea();
    // bool canMove = !(ballsInLeftArea >= maxNumberOfBallsInLeftArea && !this->inLeftArea && this->x == Window::getWallLeftPadding());
    // if(!canMove)
    //     cv.wait(lock);
    // lock.unlock();

    // if(canMove)
}

#pragma region MOVEMENT
void Customer::goToShopCounter()
{
    while (this->x >= 12)
    {
        this->x--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % maxSpeed + minSpeed));
    }
}

void Customer::goToShopQueue()
{
    while (this->y >= 43)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % maxSpeed + minSpeed));
    }
}

void Customer::goToShopCashBox(int cashBoxNumber)
{
    //y=42 x=12
    switch (cashBoxNumber)
    {
    case 1:
        goToFirstCashBox();
        break;
    case 2:
        goToSecondCashBox();
        break;
    case 3:
        goToThirdCashBox();
        break;
    default:
        break;
    }
}

void Customer::goToFirstCashBox()
{
    while (this->y >= 38)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
    }
    while (this->x >= 4)
    {
        this->x--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
    }

    while (this->y >= 15)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
    }
}

void Customer::goToSecondCashBox()
{
    while (this->y >= 38)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
    }
    while (this->x <= 12)
    {
        this->x++;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
    }

    while (this->y >= 15)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
    }
}

void Customer::goToThirdCashBox()
{
    while (this->y >= 38)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
    }
    while (this->x <= 22)
    {
        this->x++;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
    }

    while (this->y >= 15)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
    }
}

void Customer::goToFrontDoors()
{
    while (this->y >= 7)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
    }

    while (this->x <= 29)
    {
        this->x++;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
    }

    while (this->y <= 99)
    {
        this->y++;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
    }
}
#pragma endregion

std::thread Customer::moveThread()
{
    return std::thread(&Customer::move, this);
}