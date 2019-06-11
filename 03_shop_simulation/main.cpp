#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <random>
#include <chrono>
#include <vector>
#include <fstream>
#include "include/Window.h"
#include "include/ShopCounter.h"
#include "include/Customer.h"
#include "include/Data.h"

extern void printToFile(std::string data);

Window *window;
ShopCounter *shopCounter;
std::vector<std::thread> generatingThreads;
std::vector<Customer*> customers;

bool running = true;


void createCustomers()
{
    //6
    customers.push_back(new Customer(27, 90, rand() % 10, rand() % 10, rand() % 10, 3));
    customers.push_back(new Customer(27, 95, rand() % 10, rand() % 10, rand() % 10, 4));
    customers.push_back(new Customer(27, 100, rand() % 10, rand() % 10, rand() % 10, 5));
    customers.push_back(new Customer(27, 105, rand() % 10, rand() % 10, rand() % 10, 6));
    customers.push_back(new Customer(27, 110, rand() % 10, rand() % 10, rand() % 10, 7));
    customers.push_back(new Customer(27, 115, rand() % 10, rand() % 10, rand() % 10, 8));
}


void renderScene()
{
    while(running)
    {
        window->renderScene();
    }
}

void generateResources()
{
    generatingThreads.push_back(shopCounter->generateEggsThread());
    generatingThreads.push_back(shopCounter->generateMeatsThread());
    generatingThreads.push_back(shopCounter->generateRollsThread());
}

void checkIfRunning()
{
    cbreak();
    noecho();
    while('x' != getch())
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    running = false;
}

void printToFile(std::string data)
{
    std::ofstream myfile("logfile.txt", std::ios_base::app | std::ios_base::out);
    myfile <<  data + " " << std::endl;
    myfile.close();
}


int main(int argc, char *argv[  ])
{
    srand(time(NULL));
    window = new Window();  
    shopCounter = new ShopCounter();
    createCustomers();

    std::thread generateResourcesThread(generateResources);
    std::thread renderSceneThread(renderScene);
    std::thread checkIfRunningThread(checkIfRunning);

    renderSceneThread.join();
    checkIfRunningThread.join();
    generateResourcesThread.join();
    return 0;
}