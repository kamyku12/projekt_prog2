#include <iostream>
#include "olcConsoleGameEngine.h"
#include <string>
#include <vector>
#include <cstdlib>

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
    float *x,*y,*pomx,*pomy;
    wchar_t znak, znak_srodek;
    int color, color_srodek, szerokosc, wysokosc;
    bool shootable;
    wchar_t znaki[5] = {'M','O','W','A','R'};
public:
    Kosmita(int lp)
    {
        this->x = new float[3];
        this->pomx = new float[3];
        this->y = new float[3];
        this->pomy = new float[3];
        this->szerokosc = 4;
        this->wysokosc = 4;
        this->znak_srodek = L' ';
        this->znak = L'A';
        this->color = 164;
        this->color_srodek = 240;
        this->shootable = true;

        for (int i = 0; i < this->szerokosc; i++)
        {
            this->x[i] = 50.0f + lp * (this->szerokosc*2) + i;
            this->pomx[i] = this->x[i];
        }
        for (int i = 0; i < this->wysokosc; i++)
        {
            this->y[i] = 15.0f + i;
            this->pomy[i] = this->y[i];
        }
        
    }

    float Kosmitax(int which) { return this->x[which]; }
    int Szerokosc() { return this->szerokosc; }
    float Kosmitay(int which) { return this->y[which]; }
    float Wysokosc() { return this->wysokosc; }
    wchar_t Kosmitaznak() { return this->znak; }
    wchar_t Kosmitaznak_sr() { return this->znak_srodek; }
    int Kosmitacolor() { return this->color; }
    int Kosmitacolor_sr() { return this->color_srodek; }
    bool Shootable() { return this->shootable; }
    void Kosmitaznak(char znak) { this->znak = znak; this->znak_srodek = znak; }
    void Kosmitacolor(int color) { this->color = color; this->color_srodek = color;}
    void Shootable_zmien() { this->shootable = false; }
    void Shootable_zmien(bool which) { this->shootable = which; }
    void Kosmita_poczatek() 
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
    void Kosmitay_wdol(float where) 
    { 
        for(int i = 0; i < this->wysokosc; i++)
            this->y[i] += where;
    }

    void Move(float fElapsedTime, bool left)
    {
        if (left)
        {
            for(int i = 0; i < this->szerokosc; i++)
                this->x[i] -= 15.0f * fElapsedTime;
        }
        else
        {
            for(int i = 0; i < this->szerokosc; i++)
                this->x[i] += 15.0f * fElapsedTime;
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
    Kosmita *kosmita[6];
    int score, ile;
    wstring wscore;
    wstring string1;
public:
    Gra()
    {
        ile = 6;
        for (int i = 0; i < ile; i++)
            kosmita[i] = new Kosmita(i);
        ruchwlewo = true;
        wystrzelony = false;
        ship = new Statek;
        pociskgracz = new Pocisk;
        score = 0;
        wscore = L"Score: ";
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
        for (int which = 0; which < ile; which++)
        {
            for (int x = 0; x < kosmita[which]->Szerokosc(); x++)
                for (int y = 0; y < kosmita[which]->Wysokosc(); y++)
                    if ((x == 1 || x == 2) && (y == 1 || y == 2)) Draw(kosmita[which]->Kosmitax(x), kosmita[which]->Kosmitay(y), kosmita[which]->Kosmitaznak_sr(), kosmita[which]->Kosmitacolor_sr());
                    else Draw(kosmita[which]->Kosmitax(x), kosmita[which]->Kosmitay(y), kosmita[which]->Kosmitaznak(), kosmita[which]->Kosmitacolor());
        }
        
        //Ruch Kosmity
        for (int which = 0; which < ile; which++)
        {
            kosmita[which]->Move(fElapsedTime, ruchwlewo);
        }

        if (kosmita[0]->Kosmitax(0) < 1.5f)
        {
            for (int i = 0; i < ile; i++)
                for (int y = 0; y < 3; y++)
                    kosmita[i]->Kosmitay_wdol(1.0f);

            ruchwlewo = false;
        }
            
        if (kosmita[ile - 1]->Kosmitax(3) > 118.0f)
        {
            for (int i = 0; i < ile; i++)
                for (int y = 0; y < 3; y++)
                    kosmita[i]->Kosmitay_wdol(1.0f);

            ruchwlewo = true;
        }

        //Pomoc przy kolizji
        /*
        string1 = to_wstring(kosmita[5]->Kosmitay(2));
        DrawString(10, 21, string1, 15);
        string1 = to_wstring(kosmita[1]->Kosmitay(1));
        DrawString(10, 22, string1, 164);
        string1 = to_wstring(kosmita[1]->Kosmitay(2));
        DrawString(10, 23, string1, 15);
        */
        

        //Kolizja kosmita
        for (int which = 0; which < ile; which++)
        {
                    if ((pociskgracz->Pociskx() >= kosmita[which]->Kosmitax(0) + 0.5f && pociskgracz->Pociskx() <= kosmita[which]->Kosmitax(2)+0.5f) && (pociskgracz->Pocisky() >= kosmita[which]->Kosmitay(0)+0.5f && pociskgracz->Pocisky() <= kosmita[which]->Kosmitay(2)+0.5f) && kosmita[which]->Shootable() == true)
                    {
                        pociskgracz->Pocisky(64.0f);
                        wystrzelony = false;
                        kosmita[which]->Kosmitaznak(' ');
                        kosmita[which]->Kosmitacolor(0);
                        kosmita[which]->Shootable_zmien();
                        score += 100;
                    }
                    if (kosmita[0]->Shootable() == false && kosmita[1]->Shootable() == false && kosmita[2]->Shootable() == false && kosmita[3]->Shootable() == false && kosmita[4]->Shootable() == false && kosmita[5]->Shootable() == false)
                    {
                        for(int ktory = 0; ktory < 6; ktory++)
                            kosmita[ktory]->Kosmita_poczatek();
                    }
        }

        //Punkty
        DrawString(1, 1, wscore, 15);
        DrawString(8, 1, to_wstring(score), 15);


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