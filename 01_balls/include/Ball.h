#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <thread>
#include <ncurses.h>
#include "../enums/direction.h"

class Ball
{
public:
    Ball();
    Ball(int x, int y, int slow, int xDirection, int yDirection);
    ~Ball();

    static void drawScene(int windowX, int windowY);

    void move();
    int getX();
    int getY();
    int getSlow();
    int getPreviousX();
    int getPreviousY();
    void printLogs();
    std::thread moveThread();


private:
    static int xMax;
    static int yMax;
    int x;
    int y;
    int previousX;
    int previousY;
    int xDirection;
    int yDirection;
    int slow;
};

#endif