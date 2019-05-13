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
    static int getBallsInLeftArea();
    static void setBallsInLeftArea(int value);
    static int getMaxNumberOfBallsInLeftArea();
    static void setMaxNumberOfBallsInLeftArea(int value);

    void move();
    int getX();
    int getY();
    bool getInLeftArea();
    void setInLeftArea(bool value);
    void printLogs();
    void setDirection(directon ballDirection);
    void setSpeed(speed ballSpeed);
    void checkIfIsInLeftArea();

    std::thread moveThread();

private:
    static int xMax;
    static int yMax;
    static bool runningFlag;
    static int ballsInLeftArea;
    static int maxNumberOfBallsInLeftArea;
    bool inLeftArea = false;
    int x;
    int y;
    int xDirection;
    int yDirection;
    int slowdown;
};

#endif