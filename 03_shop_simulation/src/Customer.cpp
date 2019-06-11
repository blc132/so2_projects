#include "../include/Customer.h"

extern bool running;

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

std::thread Customer::moveThread()
{
    return std::thread(&Customer::move, this);
}