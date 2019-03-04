#ifndef BALL_H
#define BALL_H

#include <iostream>


class Ball
{
    public:
        Ball(int x, int y, float speed);
        ~Ball();
        void move();
        int getX();
        int getY();
        float getSpeed();
    private:
        static int xMax;
        static int yMax;
        int x;
        int y;
        float speed;
}