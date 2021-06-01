#include "Statek.h"

Statek::Statek()
{
    this->playerx1 = 59.0f;
    this->playery1 = 65.0f;
    this->playerx2 = 56.0f;
    this->playery2 = 68.0f;
    this->playerx3 = 62.0f;
    this->playery3 = 68.0f;
    this->lifes = 3;
    this->pociskgracz = new Pocisk;
}

Statek::~Statek()
{
    delete this->pociskgracz;
}

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

void Statek::Life_minus()
{
    this->lifes = this->lifes - 1;
}


int Statek::Lifes() { return this->lifes; }
float Statek::Playerx1() { return this->playerx1; }
float Statek::Playerx2() { return this->playerx2; }
float Statek::Playerx3() { return this->playerx3; }
float Statek::Playery1() { return this->playery1; }
float Statek::Playery2() { return this->playery2; }
float Statek::Playery3() { return this->playery3; }