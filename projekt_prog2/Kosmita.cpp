#include "Kosmita.h"
#include <cstdlib>
#include <time.h>


Kosmita::Kosmita(int lp, char znaczek, int freq)
{
    this->szerokosc = 5;
    this->wysokosc = 5;
    this->x = new float[szerokosc];
    this->pomx = new float[szerokosc];
    this->y = new float[wysokosc];
    this->pomy = new float[wysokosc];
    this->znak_srodek = L' ';
    this->znak = znaczek;
    this->znak_pocz = znaczek;
    this->color = 164;
    this->color_srodek = 240;
    this->shootable = true;
    this->pociskkosmita = new Pocisk;
    this->strzelic = freq;
    this->kosmwystrzelony = false;

    for (int i = 0; i < this->szerokosc; i++)
    {
        if (lp / 6 >= 1.0f)this->x[i] = 37.0f + (lp - 6) * (this->szerokosc * 2) + i;
        else this->x[i] = 37.0f + lp * (this->szerokosc * 2) + i;

        this->pomx[i] = this->x[i];
    }
    for (int i = 0; i < this->wysokosc; i++)
    {
        if (lp / 6 == 1.0f) this->y[i] = 15.0f + (this->wysokosc * 2) + i;
        else this->y[i] = 15.0f + i;
        this->pomy[i] = this->y[i];
    }
}

Kosmita::~Kosmita()
{
    delete this->pociskkosmita;
    delete this->x;
    delete this->pomy;
    delete this->y;
    delete this->pomy;
}



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

bool Kosmita::Shoot(int czas)
{
    if (strzelic == czas) return true;
    else return false;
}

bool Kosmita::wystrzelony()
{
    return this->kosmwystrzelony;
}

void Kosmita::wystrzelony(bool l)
{
    this->kosmwystrzelony = l;
}

int Kosmita::Strzelic()
{
    return this->strzelic;
}

void Kosmita::Kosmita_poczatek()
{
    srand(time(NULL));
    for (int i = 0; i < this->szerokosc; i++)
    {
        this->x[i] = this->pomx[i];
    }
    for (int i = 0; i < this->wysokosc; i++)
    {
        this->y[i] = this->pomy[i];
    }
    this->znak = this->znak_pocz;
    this->znak_srodek = L' ';
    this->color = rand()%239 + 16;
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