#pragma once
#include "Pocisk.h"

class Statek :public Pocisk
{
private:
    float playerx1;
    float playery1;
    float playerx2;
    float playery2;
    float playerx3;
    float playery3;
    int lifes;
    Pocisk* pociskgracz;
public:
    Statek();
    ~Statek();

    void Move_left(float fElapsedTime);
    void Move_right(float fElapsedTime);
    void Life_minus();

    int Lifes();
    float Playerx1();
    float Playerx2();
    float Playerx3();
    float Playery1();
    float Playery2();
    float Playery3();
};