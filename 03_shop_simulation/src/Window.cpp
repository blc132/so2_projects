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

    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void Window::renderShopCounter()
{
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    for (int i = 3; i < 10; i++)
    {
        for (int j = 90; j < 116; j++)
        {
            mvprintw(i, j, " ");
        }
    }
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(2));
    mvprintw(4, 98, (eggsLabel + std::to_string(eggsCounter)).c_str());
    mvprintw(6, 98, (rollsLabel + std::to_string(rollsCounter)).c_str());
    mvprintw(8, 98, (meatsLabel + std::to_string(meatsCounter)).c_str());
}

void Window::renderShopQueue()
{
    init_pair(3, COLOR_WHITE, COLOR_WHITE);
    attron(COLOR_PAIR(3));

    for (int i = 10; i < 15; i++)
    {
        for (int j = 50; j < 80; j++)
        {
            mvprintw(i, j, " ");
        }
    }
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(4));
    mvprintw(10, 61, "KOLEJKA");
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