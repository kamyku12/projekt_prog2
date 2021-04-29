#include "Kosmita.h"

float Kosmita::Kosmitax(int which) { return this->x[which]; }
int Kosmita::Szerokosc() { return this->szerokosc; }
float Kosmita::Kosmitay(int which) { return this->y[which]; }
float Kosmita::Wysokosc() { return this->wysokosc; }
wchar_t Kosmita::Kosmitaznak() { return this->znak; }
wchar_t Kosmita::Kosmitaznak_sr() { return this->znak_srodek; }
int Kosmita::Kosmitacolor() { return this->color; }
int Kosmita::Kosmitacolor_sr() { return this->color_srodek; }
bool Kosmita::Shootable() { return this->shootable; }

void Kosmita::Kosmitaznak(char znak) { this->znak = znak; this->znak_srodek = znak; }
void Kosmita::Kosmitacolor(int color) { this->color = color; this->color_srodek = color; }
void Kosmita::Shootable_zmien() { this->shootable = false; }

void Kosmita::Kosmita_poczatek()
{
    for (int i = 0; i < this->szerokosc; i++)
    {
        this->x[i] = this->pomx[i];
        this->y[i] = this->pomy[i];
    }
    this->znak = L'A';
    this->znak_srodek = L' ';
    this->color = 164;
    this->color_srodek = 240;
    this->shootable = true;
}

void Kosmita::Kosmitay_wdol(float where)
{
    for (int i = 0; i < this->wysokosc; i++)
        this->y[i] += where;
}

void Kosmita::Move(float fElapsedTime, bool left, int level)
{
    if (left)
    {
        for (int i = 0; i < this->szerokosc; i++)
            this->x[i] -= 15.0f * (1 + 0.20*(level-1)) * fElapsedTime;
    }
    else
    {
        for (int i = 0; i < this->szerokosc; i++)
            this->x[i] += 15.0f * (1 + 0.20 * (level - 1)) * fElapsedTime;
    }
}