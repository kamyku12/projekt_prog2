#pragma once
#include "Pocisk.h"
#include <vector>
#include <cstdlib>

class Statek :public Pocisk
{
private:
    std::vector<float> playerx, playery;
    int lifes;
    bool wystrzelony;
    Pocisk* pociskgracz;
public:
    Statek();
    ~Statek();

    void Move_left(float fElapsedTime);
    void Move_right(float fElapsedTime);
    void Life_minus();
    void Wystrzelony(bool wystrzelony);

    int Lifes();
    float Playerx(int which);
    float Playery(int which);
    bool Wystrzelony();
};