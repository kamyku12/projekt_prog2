#pragma once
#include "Pocisk.h"

class Kosmita : public Pocisk
{
private:
    float* x, * y, * pomx, * pomy;
    wchar_t znak, znak_srodek, znak_pocz;
    int color, color_srodek, szerokosc, wysokosc, strzelic;
    bool shootable, kosmwystrzelony;
    wchar_t znaki[5] = { 'M','O','W','A','R' };
    Pocisk* pociskkosmita;
public:
    Kosmita(int lp, char znaczek, int freq);
    ~Kosmita();

    float Kosmitax(int which);
    int Szerokosc();
    float Kosmitay(int which);
    float Wysokosc();
    wchar_t Kosmitaznak();
    wchar_t Kosmitaznak_sr();
    int Kosmitacolor();
    int Kosmitacolor_sr();
    bool Shootable();
    bool Shoot(int czas);
    bool wystrzelony();

    int Strzelic();


    void wystrzelony(bool l);
    void Kosmitaznak(char znak);
    void Kosmitacolor(int color);
    void Shootable_zmien();

    void Kosmita_poczatek();

    void Kosmitay_wdol(float where);

    void Move(float fElapsedTime, bool left, int level);
};

