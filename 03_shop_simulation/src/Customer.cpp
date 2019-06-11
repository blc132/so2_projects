#include "../include/Customer.h"


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

void Customer::goToShopCounter()
{

}