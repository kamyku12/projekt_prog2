#pragma once
#include "Pocisk.h"
#include <cstdlib>
#include <vector>

class Kosmita : public Pocisk
{
private:
    std::vector<float> x, y, pomx, pomy;
    wchar_t znak, znak_srodek, znak_pocz;
    int color, color_srodek, szerokosc, wysokosc, strzelic;
    bool shootable, kosmwystrzelony, ruchwlewo;
    std::vector<wchar_t> znaki = { 'M','O','W','A','R' };
    Pocisk* pocisk_kosmita;
public:
    Kosmita(int lp, int znaczek, int freq);
    ~Kosmita();

    float Kosmitax(int which);
    int Szerokosc();
    float Kosmitay(int which);
    float Wysokosc();
    wchar_t Kosmita_znak();
    wchar_t Kosmita_znak_sr();
    int Kosmita_color();
    int Kosmita_color_sr();
    bool Shootable();
    bool Shoot(int czas);
    bool wystrzelony();

    int Strzelic();


    void wystrzelony(bool l);
    void Kosmita_znak(char znak);
    void Kosmita_color(int color);
    void Shootable_zmien();
    void Ruch_w_lewo(bool wlewo);

    void Kosmita_poczatek();

    void Kosmitay_wdol(float where);

    void Move(float fElapsedTime, int level);
};

