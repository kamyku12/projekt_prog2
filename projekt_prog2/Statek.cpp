#include "Statek.h"

Statek::Statek()
{
    this->playerx.push_back(59.0f);
    this->playerx.push_back(56.0f);
    this->playerx.push_back(62.0f);

    this->playery.push_back(65.0f);
    this->playery.push_back(68.0f);
    this->playery.push_back(68.0f);

    this->lifes = 3;
    this->pociskgracz = new Pocisk;
    this->wystrzelony = false;
}

Statek::~Statek()
{
    delete this->pociskgracz;
    this->playerx.clear();
    this->playery.clear();
}

void Statek::Move_left(float fElapsedTime)
{
    if (playerx[1] > 2.0f)
    {
        for (int x = 0; x < 3; x++)
           this->playerx[x] -= 35.0f * fElapsedTime;
    }
}

void Statek::Move_right(float fElapsedTime)
{
    if (playerx[2] < 118.0f)
    {
        for (int x = 0; x < 3; x++)
            this->playerx[x] += 35.0f * fElapsedTime;
    }
}

void Statek::Life_minus()
{
    this->lifes -= 1;
}

void Statek::Wystrzelony(bool wystrzelony)
{
    this->wystrzelony = wystrzelony;
}


int Statek::Lifes() { return this->lifes; }
float Statek::Playerx(int which) { return this->playerx[which-1]; }
float Statek::Playery(int which) { return this->playery[which-1]; }

bool Statek::Wystrzelony() { return this->wystrzelony; }
