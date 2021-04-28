#include "Statek.h"

void Statek::Move_left(float fElapsedTime)
{
    if (playerx2 > 2.0f)
    {
        this->playerx1 -= 35.0f * fElapsedTime;
        this->playerx2 -= 35.0f * fElapsedTime;
        this->playerx3 -= 35.0f * fElapsedTime;
    }
}

void Statek::Move_right(float fElapsedTime)
{
    if (playerx3 < 118.0f)
    {
        this->playerx1 += 35.0f * fElapsedTime;
        this->playerx2 += 35.0f * fElapsedTime;
        this->playerx3 += 35.0f * fElapsedTime;
    }
}

float Statek::Playerx1() { return this->playerx1; }
float Statek::Playerx2() { return this->playerx2; }
float Statek::Playerx3() { return this->playerx3; }
float Statek::Playery1() { return this->playery1; }
float Statek::Playery2() { return this->playery2; }
float Statek::Playery3() { return this->playery3; }