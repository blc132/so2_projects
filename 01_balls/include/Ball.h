#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <thread>
#include "../enums/direction.h"

class Ball
{
    public:
        Ball();
        Ball(int x, int y, int speed, int xDirection, int yDirection);
        ~Ball();
        
        static void initScene(int windowX, int windowY);
        
        void move();
        int getX();
        int getY();
        int getSpeed();
        void printLogs();
        std::thread moveThread();

        
    private:
        static int xMax;
        static int yMax;
        int x;
        int y;
        int xDirection;
        int yDirection;
        int speed;
};

#endif