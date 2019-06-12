#include "../include/Customer.h"

extern void printToFile(std::string data);

extern bool running;
extern int eggsCounter;
extern int rollsCounter;
extern int meatsCounter;
extern bool isCashboxFree[3];

extern std::vector<Customer *> waitingToShopCounterCustomers;
extern std::vector<Customer *> waitingToShopCashBoxCustomers;
extern std::vector<Customer *> customers;

std::mutex shopCounterMutex;
std::mutex getResourcesMutex;
std::mutex shopQueueMutex;
std::mutex vectorMutex;
std::condition_variable cv;

Customer::Customer()
{
}

Customer::~Customer()
{
}

Customer::Customer(int x, int y, int customSpeed, int needOfEggs, int needOfRolls, int needOfMeats, short color, int id)
{
    this->x = x;
    this->y = y;
    this->needOfEggs = needOfEggs;
    this->needOfRolls = needOfRolls;
    this->needOfMeats = needOfMeats;
    this->customSpeed = customSpeed;
    this->color = color;
    this->id = id;
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
        interactionWithCashBoxQueue();
        std::this_thread::sleep_for(std::chrono::milliseconds(pauseBetweenMoves));
        interactionWithCashBox();
        goToShopCashBox(whichCashbox);
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 5000 + 2000));
        leaveCashbox();
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
    // std::unique_lock<std::mutex> vectorLock(vectorMutex);
    if (!inShopCounterQueue())
    {
        // printToFile("DODANO, gracz nr: " + std::to_string(id));
        waitingToShopCounterCustomers.push_back(this);
    }
    // vectorLock.unlock();

    bool shopHasAllProducts = false;
    while (!shopHasAllProducts)
    {
        std::unique_lock<std::mutex> lock(shopCounterMutex);

        if (!isFirstInShopCounterQueue())
        {
            // printToFile("LOCK, gracz nr: " + std::to_string(id));
            cv.wait(lock);
        }
        else
        {
            // printToFile("FIRST, gracz nr: " + std::to_string(id));
            shopHasAllProducts = (needOfEggs <= eggsCounter && needOfMeats <= meatsCounter && needOfRolls <= rollsCounter);

            if (shopHasAllProducts)
            {
                eggsCounter -= needOfEggs;
                rollsCounter -= needOfRolls;
                meatsCounter -= needOfMeats;
                cv.notify_all();

                waitingToShopCounterCustomers.erase(waitingToShopCounterCustomers.begin());
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        lock.unlock();
    }
}

void Customer::interactionWithCashBoxQueue()
{
    // isCashboxFree[0] = true;
    // std::unique_lock<std::mutex> vectorLock(vectorMutex);
    if (!inCashboxQueue())
    {
        printToFile("DODANO, gracz nr: " + std::to_string(id));
        waitingToShopCashBoxCustomers.push_back(this);
        moveInQueue();
    }
    // vectorLock.unlock();

    bool cashBoxIsFree = false;
    while (!cashBoxIsFree)
    {
        std::unique_lock<std::mutex> lock(shopQueueMutex);

        if (!isFirstInCashboxQueue())
        {
            printToFile("LOCK, gracz nr: " + std::to_string(id));
            cv.wait(lock);
        }
        else
        {
            printToFile("FIRST, gracz nr: " + std::to_string(id));
            cashBoxIsFree = isCashboxFree[0] || isCashboxFree[1] || isCashboxFree[2];

            if (cashBoxIsFree)
            {
                if (isCashboxFree[0])
                {
                    // goToFirstCashBox();
                    whichCashbox = 1;
                    isCashboxFree[0] = false;
                }
                else if (isCashboxFree[1])
                {
                    // goToSecondCashBox();
                    whichCashbox = 2;
                    isCashboxFree[1] = false;
                }
                else
                {
                    // goToThirdCashBox();
                    whichCashbox = 3;
                    isCashboxFree[2] = false;
                }
                cv.notify_all();

                waitingToShopCashBoxCustomers.erase(waitingToShopCashBoxCustomers.begin());
                moveAllInQueue();
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        lock.unlock();
    }
}

void Customer::interactionWithCashBox()
{
}

void Customer::leaveCashbox()
{
    switch (whichCashbox)
    {
    case 1:
        isCashboxFree[0] = true;
        break;
    case 2:
        isCashboxFree[1] = true;
        break;
    case 3:
        isCashboxFree[2] = true;
        break;
    default:
        break;
    }
}

bool Customer::inShopCounterQueue()
{
    // printToFile("inShopCounterQueue");
    for (int i = 0; i < waitingToShopCounterCustomers.size(); i++)
    {
        // printToFile("waitinID: " + std::to_string(waitingToShopCounterCustomers[i]->getId()) + " currentID: " + std::to_string(customers[j]->getId()));
        if (waitingToShopCounterCustomers[i]->getId() == id)
            return true;
    }
    return false;
}

bool Customer::isFirstInShopCounterQueue()
{
    for (int j = 0; j < customers.size(); j++)
    {
        if (waitingToShopCounterCustomers[0]->getId() == id)
            return true;
    }
    return false;
}

bool Customer::inCashboxQueue()
{
    for (int i = 0; i < waitingToShopCashBoxCustomers.size(); i++)
    {
        if (waitingToShopCashBoxCustomers[i]->getId() == id)
            return true;
    }
    return false;
}

bool Customer::isFirstInCashboxQueue()
{
    for (int j = 0; j < customers.size(); j++)
    {
        if (waitingToShopCashBoxCustomers[0]->getId() == id)
            return true;
    }
    return false;
}

#pragma region MOVEMENT
void Customer::goToShopCounter()
{
    while (this->x >= 12)
    {
        this->x--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
    }
}

void Customer::moveInQueue()
{
    int queueSize = waitingToShopCashBoxCustomers.size();
    int stepsToDo = (6 - queueSize) * 3;
    for (int i = 0; i < stepsToDo; i++)
    {
        y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
    }
}

void Customer::moveAllInQueue()
{
    for (int j = 0; j < waitingToShopCashBoxCustomers.size(); j++)
    {
        int tempY = waitingToShopCashBoxCustomers[0]->getY();
        waitingToShopCashBoxCustomers[0]->setY(tempY - 3);
    }
}

void Customer::goToShopQueue()
{
    while (this->y >= 58)
    {
        this->y--;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % (maxSpeed - this->customSpeed) + minSpeed));
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

void writeInfo()
{
}