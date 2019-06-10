#include "../include/Window.h"
#include <vector>
#include <ncurses.h>

extern void printToFile(std::string data);

Window::Window()
{
    initializeFields();
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

    renderShopCounter();
    renderShopQueue();
    renderShopCashBox(2, 10, 5, COLOR_WHITE, COLOR_WHITE, 1);
    renderShopCashBox(12, 10, 6, COLOR_WHITE, COLOR_WHITE, 2);
    renderShopCashBox(22, 10, 7, COLOR_WHITE, COLOR_WHITE, 3);
    

    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void Window::renderShopCounter()
{
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    for (int i = 4; i < 11; i++)
    {
        for (int j = 90; j < 116; j++)
        {
            mvprintw(i, j, " ");
        }
    }
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(2));
    mvprintw(5, 98, (eggsLabel + std::to_string(eggsCounter)).c_str());
    mvprintw(7, 98, (rollsLabel + std::to_string(rollsCounter)).c_str());
    mvprintw(9, 98, (meatsLabel + std::to_string(meatsCounter)).c_str());
}

void Window::renderShopQueue()
{
    init_pair(3, COLOR_WHITE, COLOR_WHITE);
    attron(COLOR_PAIR(3));

    for (int i = 12; i < 17; i++)
    {
        for (int j = 50; j < 80; j++)
        {
            mvprintw(i, j, " ");
        }
    }
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(4));
    mvprintw(12, 61, "KOLEJKA");
}

void Window::renderShopCashBox(int x, int y, short colorNumber, short textColor, short backgroundColor, short cashNumber)
{
    init_pair(colorNumber, colorNumber, backgroundColor);
    attron(COLOR_PAIR(colorNumber));

    for (int i = x; i < x+5; i++)
    {
        for (int j = y; j < y+10; j++)
        {
            mvprintw(i, j, " ");
        }
    }
    attron(COLOR_PAIR(4));
    mvprintw(x+2, y, ("KASA NR." + std::to_string(cashNumber)).c_str());
}

void Window::initializeFields()
{
    eggsLabel = "Jajka:   ";
    rollsLabel = "Bulki:   ";
    meatsLabel = "Wedliny: ";
    eggsCounter = 0;
    rollsCounter = 0;
    meatsCounter = 0;
}