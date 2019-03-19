#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include "../enums/direction.h"

class Ball
{
public:
    Ball();
    Ball(int x, int y, int slow, directon ballDirection);
    ~Ball();

    static void drawScene(int windowX, int windowY);
    static void setRunningFlag(bool flag);
    static bool getRunningFlag();

    void move();
    int getX();
    int getY();
    int getSlow();
    void printLogs();
    void setDirection(directon ballDirection);

    std::thread moveThread();

private:
    static int xMax;
    static int yMax;
    static bool runningFlag;
    int x;
    int y;
    int xDirection;
    int yDirection;
    int slow;
    directon ballDirection;
};

#endif