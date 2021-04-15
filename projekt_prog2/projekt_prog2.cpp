﻿#include <iostream>
#include "olcConsoleGameEngine.h"
#include <string>
#include <vector>

using namespace std;

class Statek
{
private:
    float playerx1;
    float playery1;
    float playerx2;
    float playery2;
    float playerx3;
    float playery3;
    int lifes;
public:
    Statek()
    {
        this->playerx1 = 60.0f;
        this->playery1 = 65.0f;
        this->playerx2 = 57.0f;
        this->playery2 = 68.0f;
        this->playerx3 = 63.0f;
        this->playery3 = 68.0f;
        this->lifes = 3;
    }

    void Move_left(float fElapsedTime)
    {
        if (playerx2 > 2.0f)
        {
            this->playerx1 -= 35.0f * fElapsedTime;
            this->playerx2 -= 35.0f * fElapsedTime;
            this->playerx3 -= 35.0f * fElapsedTime;
        }
    }

    void Move_right(float fElapsedTime)
    {
        if (playerx3 < 118.0f)
        {
            this->playerx1 += 35.0f * fElapsedTime;
            this->playerx2 += 35.0f * fElapsedTime;
            this->playerx3 += 35.0f * fElapsedTime;
        }
    }
    float Playerx1() { return this->playerx1; }
    float Playerx2() { return this->playerx2; }
    float Playerx3() { return this->playerx3; }
    float Playery1() { return this->playery1; }
    float Playery2() { return this->playery2; }
    float Playery3() { return this->playery3; }
};

class Kosmita
{
private:
    float *x,*y;
    wchar_t znak;
    int color;
    bool shootable;
public:
    Kosmita(int lp)
    {
        this->x = new float[3];
        this->y = new float[3];

        for (int i = 0; i < 3; i++)
            this->x[i] = i + 60.0f;
        for (int i = 0; i < 3; i++)
            this->y[i] = 15.0f;
        znak = L'A';
        color = 164;
        shootable = true;
    }

    float Kosmitax(int which) { return this->x[which]; }
    float Kosmitay(int which) { return this->y[which]; }
    wchar_t Kosmitaznak() { return this->znak; }
    int Kosmitacolor() { return this->color; }
    bool Shootable() { return this->shootable; }
    void Kosmitaznak(char znak) { this->znak = znak; }
    void Kosmitacolor(int color) { this->color = color; }
    void Shootable_zmien() { this->shootable = false; }
    void Kosmitax_zmien(float where) 
    { 
        this->x[0] = where;
        this->x[1] = where+1;
        this->x[2] = where+2;
    }
    void Kosmitay_zmien(float where) 
    { 
        this->y[0] = where;
        this->y[1] = where + 1;
        this->y[2] = where + 2;
    }

    void Move(float fElapsedTime, bool left)
    {
        if (left)
        {
            this->x[0] -= 15.0f * fElapsedTime;
            this->x[1] -= 15.0f * fElapsedTime;
            this->x[2] -= 15.0f * fElapsedTime;
        }
        else
        {
            this->x[0] += 15.0f * fElapsedTime;
            this->x[1] += 15.0f * fElapsedTime;
            this->x[2] += 15.0f * fElapsedTime;
        }
    }
};

class Pocisk
{
private:
    float pocisky, pociskx;
    bool up;
public:
    Pocisk()
    {
        this->pocisky = 64.0f;
        this->pociskx = 0.0f;
        this->up = true;
    }

    void Move_up(float fElapsedTime)
    {
        this->up = true;
        if (this->up == true && this->pocisky > 2.0f) this->pocisky -= 50.0f * fElapsedTime;
    }

    void Move_down(float fElapsedTime)
    {
        this->up = false;
        if (this->up == false) this->pocisky += 50.0f * fElapsedTime;
    }

    float Pociskx() { return this->pociskx; }
    float Pocisky() { return this->pocisky; }
    void Pociskx(float x) { this->pociskx = x; }
    void Pocisky(float y) { this->pocisky = y; }
};


class Gra : public olcConsoleGameEngine
{
private:
    Statek* ship;
    Pocisk* pociskgracz;
    bool wystrzelony;
    bool ruchwlewo;
    Kosmita *kosmita[3];
    wstring string1;
public:
    Gra()
    {
        for (int i = 0; i < 3; i++)
            kosmita[i] = new Kosmita(i+1);
        ruchwlewo = true;
        wystrzelony = false;
        ship = new Statek;
        pociskgracz = new Pocisk;
    }

    virtual bool OnUserCreate()
    {
        
        
        return true;
    }

    virtual bool OnUserUpdate(float fElapsedTime)
    {
        //Ruch statku
        if (m_keys[VK_LEFT].bHeld)
        {
            ship->Move_left(fElapsedTime);
        }
        if (m_keys[VK_RIGHT].bHeld)
        {
            ship->Move_right(fElapsedTime);
        }

        //Rysowanie obramowania
        for (int i = 0; i < 80; i++)
            for (int j = 0; j < 160; j++)
                if (i == 0 || j == 0 || i == m_nScreenHeight - 1 || j == m_nScreenWidth - 1) Draw(j, i, L'#', 15);
                else Draw(j, i, L' ', 0);


        //Rysowanie statku
        DrawTriangle(ship->Playerx1(), ship->Playery1(), ship->Playerx2(), ship->Playery2(), ship->Playerx3(), ship->Playery3(), L'#', 14);
        FillTriangle(ship->Playerx1(), ship->Playery1(), ship->Playerx2(), ship->Playery2(), ship->Playerx3(), ship->Playery3(), L'#', 14);

        //Rysowanie pocisku, ruch pocisku
        if (m_keys[VK_SPACE].bPressed && wystrzelony == false)
        {
            wystrzelony = true;
            pociskgracz->Pociskx(ship->Playerx1());
        }

        if (wystrzelony == true)
        {

            Draw(pociskgracz->Pociskx(), pociskgracz->Pocisky(), L'O', 15);
            pociskgracz->Move_up(fElapsedTime);
            if (pociskgracz->Pocisky() <= 2.0f)
            {
                pociskgracz->Pocisky(64.0f);
                pociskgracz->Pociskx(ship->Playerx1());
                wystrzelony = false;
            }
        }

        //Rysowanie Kosmity
        for (int which = 0; which < 3; which++)
        {
            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++)
                    if (x == 1 && y == 1) Draw(kosmita[which]->Kosmitax(x), kosmita[which]->Kosmitay(y), L' ', 0);
                    else Draw(kosmita[which]->Kosmitax(x), kosmita[which]->Kosmitay(y), kosmita[which]->Kosmitaznak(), kosmita[which]->Kosmitacolor());
        }
        
        for (int which = 0; which < 3; which++)
        {
            //kosmita[which].Move(fElapsedTime, ruchwlewo);
        }

            if (kosmita[0]->Kosmitax(0) < 2.0f) ruchwlewo = false;
            if (kosmita[2]->Kosmitax(2) > 106.0f) ruchwlewo = true;
        

        //Pomoc przy kolizji

        string1 = to_wstring(kosmita[0]->Kosmitax(0));
        DrawString(10, 21, string1, 15);
        string1 = to_wstring(kosmita[1]->Kosmitax(0));
        DrawString(10, 22, string1, 164);
        string1 = to_wstring(kosmita[2]->Kosmitax(0));
        DrawString(10, 23, string1, 15);

        //Kolizja z kosmita
        
        for (int which = 0; which < 3; which++)
        {
            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++)
                    if ((pociskgracz->Pociskx() > kosmita[which]->Kosmitax(x) - 0.5 && pociskgracz->Pociskx() < kosmita[which]->Kosmitax(x) + 0.5) && pociskgracz->Pocisky() < kosmita[which]->Kosmitay(y) && kosmita[which]->Shootable() == true)
                    {
                        pociskgracz->Pocisky(64.0f);
                        wystrzelony = false;
                        kosmita[which]->Kosmitaznak(' ');
                        kosmita[which]->Kosmitacolor(123);
                        kosmita[which]->Shootable_zmien();
                    }
        }

        return true;
    }
};




int main()
{
    Gra gierka;
    gierka.ConstructConsole(120, 70, 8, 8);
    gierka.Start();

    system("PAUSE");
    return 0;
}

