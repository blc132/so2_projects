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
std::vector<Customer *> customers;
std::vector<Customer *> waitingToShopCounterCustomers;
std::vector<Customer *> waitingToShopCashBoxCustomers;
std::vector<std::thread> customersThreads;

bool running = true;
bool isCashboxFree[3];

void createCustomers()
{
    //6
    customers.push_back(new Customer(27, 100, rand() % 200 + 0, rand() % 10, rand() % 10, rand() % 10, 3, 1));
    customersThreads.push_back(customers.back()->moveThread());
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));

    customers.push_back(new Customer(27, 100, rand() % 200 + 0, rand() % 10, rand() % 10, rand() % 10, 4, 2));
    customersThreads.push_back(customers.back()->moveThread());
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));

    customers.push_back(new Customer(27, 100, rand() % 200 + 0, rand() % 10, rand() % 10, rand() % 10, 5, 3));
    customersThreads.push_back(customers.back()->moveThread());
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));

    customers.push_back(new Customer(27, 100, rand() % 200 + 0, rand() % 10, rand() % 10, rand() % 10, 6, 4));
    customersThreads.push_back(customers.back()->moveThread());
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));

    customers.push_back(new Customer(27, 100, rand() % 200 + 0, rand() % 10, rand() % 10, rand() % 10, 7, 5));
    customersThreads.push_back(customers.back()->moveThread());
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));

    customers.push_back(new Customer(27, 100, rand() % 200 + 0, rand() % 10, rand() % 10, rand() % 10, 8, 6));
    customersThreads.push_back(customers.back()->moveThread());
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));
}

void renderScene()
{
    while (running)
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

void terminateThreadsOfCustomers()
{
    for (int i = 0; i < customersThreads.size(); ++i)
    {
        customersThreads[i].join();
    }
}

void terminateThreadsOfGenerating()
{
    for (int i = 0; i < generatingThreads.size(); ++i)
    {
        generatingThreads[i].join();
    }
}
void checkIfRunning()
{
    cbreak();
    noecho();
    while ('x' != getch())
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    running = false;
}

void printToFile(std::string data)
{
    std::ofstream myfile("logfile.txt", std::ios_base::app | std::ios_base::out);
    myfile << data + " " << std::endl;
    myfile.close();
}

int main(int argc, char *argv[])
{
    printToFile("-----------------");
    isCashboxFree[0] = true;
    isCashboxFree[1] = true;
    isCashboxFree[2] = true;
    srand(time(NULL));
    window = new Window();
    shopCounter = new ShopCounter();

    std::thread generateResourcesThread(generateResources);
    std::thread renderSceneThread(renderScene);
    std::thread checkIfRunningThread(checkIfRunning);
    createCustomers();

    renderSceneThread.join();
    checkIfRunningThread.join();
    generateResourcesThread.join();
    terminateThreadsOfCustomers();
    terminateThreadsOfGenerating();
    return 0;
}