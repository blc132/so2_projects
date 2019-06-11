#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <vector>
#include <mutex>
#include <random>
#include <chrono>
#include <condition_variable>

class Customer
{
public:
    int const minSpeed = 20;
    int const maxSpeed = 30;
    int const pauseBetweenMoves = 200;

    Customer();
    Customer(int x, int y, int customSpeed, int needOfEggs, int needOfRolls, int needOfMeats, short color);
    ~Customer();
    void setX(int x) { this->x = x; }
    int getX() { return this->x; }
    void setY(int y) { this->y = y; }
    int getY() { return this->y; }
    void setNeedOfEggs(int needOfEggs) { this->needOfEggs = needOfEggs; }
    int getNeedOfEggs() { return this->needOfEggs; }
    void setNeedOfRolls(int needOfRolls) { this->needOfRolls = needOfRolls; }
    int getNeedOfRolls() { return this->needOfRolls; }
    void setNeedOfMeats(int needOfMeats) { this->needOfMeats = needOfMeats; }
    int getNeedOfMeats() { return this->needOfMeats; }
    void setColor(int color) { this->color = color; }
    int getColor() { return this->color; }
    void setInfo(std::string info) { this->info = info; }
    std::string getInfo() { return this->info; }
    void setCustomSpeed(int customSpeed) { this->customSpeed = customSpeed; }
    int getCustomSpeed() { return this->customSpeed; }
    void setHasShopping(bool hasShopping) { this->hasShopping = hasShopping; }
    bool getHasShopping() { return this->hasShopping; }

    void move();
    std::thread moveThread();

private:
    int x;
    int y;
    int customSpeed;
    int needOfEggs;
    int needOfRolls;
    int needOfMeats;
    short color;
    std::string info;
    bool hasShopping = false;

    void goToShopCounter();
    void goToShopQueue();
    void goToShopCashBox(int cashBoxNumber);
    void goToFirstCashBox();
    void goToSecondCashBox();
    void goToThirdCashBox();
    void goToFrontDoors();
    void interactionWithShopCounter();
};

#endif