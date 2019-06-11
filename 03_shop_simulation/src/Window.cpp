#include "../include/Window.h"

extern void printToFile(std::string data);
extern int eggsCounter;
extern int rollsCounter;
extern int meatsCounter;
extern std::vector<Customer *> customers;

Window::Window()
{
    //width: 122 height: 32
    initscr();
    noecho();
    curs_set(FALSE);
    clear();
    refresh();
    getmaxyx(stdscr, height, width);

    if (has_colors() == FALSE)
    {
        printToFile("Terminal nie obsługuje kolorów!\n");
        refresh();
        endwin();
        exit(1);
    }
    if (start_color() == ERR)
    {
        printToFile("Błąd: start_color()\n");
        refresh();
        endwin();
        exit(1);
    }
}

Window::~Window()
{
    endwin();
}

#pragma region GETTERS_SETTERS
int Window::getHeight()
{
    return this->height;
}

int Window::getWidth()
{
    return this->width;
}
#pragma endregion

void Window::renderScene()
{
    clear();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_YELLOW, COLOR_BLACK);

    renderShopQueue();
    renderCustomers();
    renderWalls();
    renderShopCounter();
    renderShopCashBox(2, 10, 1, 1);
    renderShopCashBox(12, 10, 1, 2);
    renderShopCashBox(22, 10, 1, 3);
    renderFrontDoors();

    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Window::renderShopCounter()
{
    attron(COLOR_PAIR(1));
    for (int i = 4; i < 11; i++)
    {
        for (int j = 89; j < 119; j++)
        {
            mvprintw(i, j, " ");
        }
    }
    attron(COLOR_PAIR(2));
    mvprintw(5, 98, ("Jajka:   " + std::to_string(eggsCounter)).c_str());
    mvprintw(7, 98, ("Bulki:   " + std::to_string(rollsCounter)).c_str());
    mvprintw(9, 98, ("Wedliny: " + std::to_string(meatsCounter)).c_str());
}

void Window::renderShopQueue()
{
    attron(COLOR_PAIR(1));
    for (int i = 14; i < 17; i++)
    {
        for (int j = 42; j < 75; j++)
        {
            mvprintw(i, j, " ");
        }
    }
    attron(COLOR_PAIR(2));
    mvprintw(10, 42, "             KOLEJKA             ");
}

void Window::renderShopCashBox(int x, int y, short colorNumber, short cashNumber)
{
    attron(COLOR_PAIR(colorNumber));
    for (int i = y; i < y + 10; i++)
    {
        mvprintw(x + 4, i, " ");
    }

    for (int i = x; i < x + 5; i++)
    {
        mvprintw(i, y, " ");
    }

    for (int i = x; i < x + 5; i++)
    {
        mvprintw(i, y + 10, " ");
    }

    attron(COLOR_PAIR(2));
    mvprintw(x - 1, y, ("KASA NR. " + std::to_string(cashNumber) + " ").c_str());
}

void Window::renderFrontDoors()
{
    attron(COLOR_PAIR(1));
    for (int i = 27; i < 28; i++)
    {
        for (int j = 105; j < 119; j++)
        {
            mvprintw(i, j, " ");
        }
    }
    attron(COLOR_PAIR(2));
    mvprintw(27, 106, "WEJSCIE");
    mvprintw(27, 11, "WYJSCIE");
}

void Window::renderCustomers()
{
    for (int i = 0; i < customers.size(); i++)
    {
        int x = customers[i]->getX();
        int y = customers[i]->getY();
        int eggs = customers[i]->getNeedOfEggs();
        int rolls = customers[i]->getNeedOfRolls();
        int meats = customers[i]->getNeedOfMeats();
        short color = customers[i]->getColor();
        attron(COLOR_PAIR(color));
        mvprintw(x, y + 1, "o");
        mvprintw(x + 1, y, ("/" + std::to_string(i) + "\\").c_str());
        // mvprintw(x + 1, y, "/|\\");
        mvprintw(x + 2, y, "/ \\");
        mvprintw(17 + i, 42, ("KLIENT NR." + std::to_string(i) + " POTRZEBUJE: " + std::to_string(eggs) + "J/" + std::to_string(rolls) + "B/" + std::to_string(meats) + "W").c_str());
    }
}

void Window::renderWalls()
{
    attron(COLOR_PAIR(1));

    for (int j = 10; j < 99; j++)
    {
        mvprintw(27, j, " ");
    }

    for (int j = 5; j < 118; j++)
    {
        mvprintw(1, j, " ");
    }

    for (int j = 1; j < 28; j++)
    {
        mvprintw(j, 118, " ");
    }

    for (int j = 1; j < 28; j++)
    {
        mvprintw(j, 5, " ");
    }
}