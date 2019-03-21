#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include "../enums/direction.h"
#include "../enums/speed.h"

class Ball
{
public:
    Ball();
    Ball(int x, int y, speed ballSpeed, directon ballDirection);
    ~Ball();

    static void setMaximumCords(int windowX, int windowY);
    static void setRunningFlag(bool flag);
    static bool getRunningFlag();

    void move();
    int getX();
    int getY();
    void printLogs();
    void setDirection(directon ballDirection);
    void setSpeed(speed ballSpeed);

    std::thread moveThread();

private:
    static int xMax;
    static int yMax;
    static bool runningFlag;
    int x;
    int y;
    int xDirection;
    int yDirection;
    int slowdown;
};

#endif