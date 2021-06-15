#include "Kosmita.h"
#include <cstdlib>
#include <time.h>


Kosmita::Kosmita(int lp, int znaczek, int freq)
{
    this->szerokosc = 5;
    this->wysokosc = 5;
    this->znak_srodek = L' ';
    this->znak = this->znaki[znaczek];
    this->znak_pocz = this->znaki[znaczek];
    this->color = 164;
    this->color_srodek = 240;
    this->shootable = true;
    this->pocisk_kosmita = new Pocisk;
    this->strzelic = freq;
    this->kosmwystrzelony = false;
    this->ruchwlewo = true;

    for (int i = 0; i < this->szerokosc; i++)
    {
        if (lp / 6 >= 1.0f)this->x.push_back(37.0f + (lp - 6) * (this->szerokosc * 2) + i);
        else this->x.push_back(37.0f + lp * (this->szerokosc * 2) + i);

        this->pomx.push_back(this->x[i]);
    }
    for (int i = 0; i < this->wysokosc; i++)
    {
        if (lp / 6 == 1.0f) this->y.push_back(15.0f + (this->wysokosc * 2) + i);
        else this->y.push_back(15.0f + i);

        this->pomy.push_back(this->y[i]);
    }
}

Kosmita::~Kosmita()
{
    this->x.clear();
    this->pomx.clear();
    this->y.clear();
    this->pomy.clear();
}



float Kosmita::Kosmitax(int which) { return this->x[which]; }
int Kosmita::Szerokosc() { return this->szerokosc; }
float Kosmita::Kosmitay(int which) { return this->y[which]; }
float Kosmita::Wysokosc() { return this->wysokosc; }
wchar_t Kosmita::Kosmita_znak() { return this->znak; }
wchar_t Kosmita::Kosmita_znak_sr() { return this->znak_srodek; }
int Kosmita::Kosmita_color() { return this->color; }
int Kosmita::Kosmita_color_sr() { return this->color_srodek; }
bool Kosmita::Shootable() { return this->shootable; }

void Kosmita::Kosmita_znak(char znak) { this->znak = znak; this->znak_srodek = znak; }
void Kosmita::Kosmita_color(int color) { this->color = color; this->color_srodek = color; }
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

    this->Pociskx(this->Kosmitax(2));
    this->Pocisky(this->Kosmitay(0));

    this->kosmwystrzelony = false;
}

void Kosmita::Kosmitay_wdol(float where)
{
    for (int i = 0; i < this->wysokosc; i++)
        this->y[i] += where;
}

void Kosmita::Move(float fElapsedTime, int level)
{
    if (ruchwlewo)
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

void Kosmita::Ruch_w_lewo(bool wlewo)
{
    this->ruchwlewo = wlewo;
}