#include "Pocisk.h"

Pocisk::Pocisk()
{
    this->pocisky = 0.0f;
    this->pociskx = 0.0f;
    this->up = true;
}

void Pocisk::Move_up(float fElapsedTime)
{
    this->up = true;
    if (this->up == true && this->pocisky > 2.0f) this->pocisky -= 50.0f * fElapsedTime;
}

void Pocisk::Move_down(float fElapsedTime)
{
    this->up = false;
    if (this->up == false && this->pocisky < 69.0f) this->pocisky += 50.0f * fElapsedTime;
}

float Pocisk::Pociskx() { return this->pociskx; }
float Pocisk::Pocisky() { return this->pocisky; }
void Pocisk::Pociskx(float x) { this->pociskx = x; }
void Pocisk::Pocisky(float y) { this->pocisky = y; }