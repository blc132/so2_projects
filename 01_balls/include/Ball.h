#ifndef BALL_H
#define BALL_H

#include <iostream>
#include "../enums/direction.h"

class Ball
{
    public:
        Ball();
        Ball(int x, int y, float speed, directon dir);
        ~Ball();
        
        static void initScene(int windowX, int windowY);
        
        void move();
        int getX();
        int getY();
        float getSpeed();
    private:
        static int xMax;
        static int yMax;
        int x;
        int y;
        directon dir;
        float speed;
};

#endif