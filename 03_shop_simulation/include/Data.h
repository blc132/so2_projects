#include "Customer.h"
#include <vector>
namespace Data
{
extern int eggsCounter;
extern int rollsCounter;
extern int meatsCounter;
extern bool running;
extern int eggsGenerationTime;
extern int rollsGenerationTime;
extern int meatsGenerationTime;
extern std::vector<Customer *> customers;
extern std::vector<Customer *> waitingToShopCounterCustomers;
extern std::vector<Customer *> waitingToShopCashBoxCustomers;
extern bool isCashboxFree[3];
} 
