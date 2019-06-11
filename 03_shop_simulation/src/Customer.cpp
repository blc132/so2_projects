#include "../include/Customer.h"

extern bool running;

Customer::Customer()
{
}

Customer::~Customer()
{
}

Customer::Customer(int x, int y, int needOfEggs, int needOfRolls, int needOfMeats, short color)
{
    this->x = x;
    this->y = y;
    this->needOfEggs = needOfEggs;
    this->needOfRolls = needOfRolls;
    this->needOfMeats = needOfMeats;
    this->color = color;
}

void Customer::move()
{
    while (running)
    {
        goToShopCounter();
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 200));
        goToShopQueue();
        goToShopCashBox(rand() % 3 + 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 200));
        goToFrontDoors();
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
        // std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 200));
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 20));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

void Customer::goToShopQueue()
{
    while (this->y >= 43)
    {
        this->y--;
        // std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 200));
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 20));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
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
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 20));
    }
    while (this->x >= 4)
    {
        this->x--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 20));
    }

    while (this->y >= 15)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 20));
    }
}

void Customer::goToSecondCashBox()
{
    while (this->y >= 38)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 20));
    }
    while (this->x <= 12)
    {
        this->x++;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 20));
    }

    while (this->y >= 15)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 20));
    }
}

void Customer::goToThirdCashBox()
{
    while (this->y >= 38)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 20));
    }
    while (this->x <= 22)
    {
        this->x++;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 20));
    }

    while (this->y >= 15)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 20));
    }
}

void Customer::goToFrontDoors()
{
      while (this->y >= 7)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 20));
    }  

          while (this->x <= 27)
    {
        this->x++;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 20));
    }  

              while (this->y <= 100)
    {
        this->y++;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50 + 20));
    }  
}

std::thread Customer::moveThread()
{
    return std::thread(&Customer::move, this);
}