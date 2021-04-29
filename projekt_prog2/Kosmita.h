#pragma once
#include "Pocisk.h"

class Kosmita : public Pocisk
{
private:
    float* x, * y, * pomx, * pomy;
    wchar_t znak, znak_srodek, znak_pocz;
    int color, color_srodek, szerokosc, wysokosc;
    bool shootable;
    wchar_t znaki[5] = { 'M','O','W','A','R' };
    Pocisk* pociskkosmita;
public:
    Kosmita(int lp, char znaczek)
    {
        this->szerokosc = 4;
        this->wysokosc = 4;
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

    float Kosmitax(int which);
    int Szerokosc();
    float Kosmitay(int which);
    float Wysokosc();
    wchar_t Kosmitaznak();
    wchar_t Kosmitaznak_sr();
    int Kosmitacolor();
    int Kosmitacolor_sr();
    bool Shootable();

    void Kosmitaznak(char znak);
    void Kosmitacolor(int color);
    void Shootable_zmien();

    void Kosmita_poczatek();

    void Kosmitay_wdol(float where);

    void Move(float fElapsedTime, bool left, int level);
};

