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
        this->playerx1 = 59.0f;
        this->playery1 = 65.0f;
        this->playerx2 = 56.0f;
        this->playery2 = 68.0f;
        this->playerx3 = 62.0f;
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
    static int ile;
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
        this->color = 164;
        this->color_srodek = 240;
        this->shootable = true;
        ile++;

        for (int i = 0; i < this->szerokosc; i++)
        {
            if(lp/6 >= 1.0f)this->x[i] = 37.0f + (lp-6) * (this->szerokosc * 2) + i;
            else this->x[i] = 37.0f + lp * (this->szerokosc * 2) + i;

            this->pomx[i] = this->x[i];
        }
        for (int i = 0; i < this->wysokosc; i++)
        {
            if(lp/6 == 1.0f) this->y[i] = 15.0f + (this->wysokosc * 2) + i;
            else this->y[i] = 15.0f + i;
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

int Kosmita::ile = 0;

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
    bool wystrzelony, ruchwlewo;
    Kosmita *kosmita[12];
    int score, ile;
    wstring wscore, wlevel, string1;
    char znaki_kosmita[5] = { 'M','O','W','A','R' };
    int randomowa, level, trafionych;
public:
    Gra()
    {
        srand(time(NULL));
        ile = 12;
        for (int i = 0; i < ile; i++)
        {
            randomowa = rand() % 5 + 0;
            kosmita[i] = new Kosmita(i, znaki_kosmita[randomowa]);
        }
        ruchwlewo = true;
        wystrzelony = false;
        ship = new Statek;
        pociskgracz = new Pocisk;
        score = 0;
        level = 1;
        wscore = L"Score: ";
        wlevel = L"Level: ";
        trafionych = 0;
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

        //Rysowanie pustego srodka
        for (int i = 0; i < 70; i++)
            for (int j = 0; j < 120; j++)
                if (i != 0 && j != 0 && i != m_nScreenHeight - 1 && j != m_nScreenWidth - 1) Draw(j, i, L' ', 0);

        //Box na score
        for (int i = 0; i < 10; i++)
            for (int j = 100; j < 120; j++)
                if (i == 0 || j == 100 || i == 9 || j == 119) Draw(j, i, L'#', 15);
                else Draw(j, i, L' ', 0);

        //Score
        DrawString(105, 4, wscore, 15);
        DrawString(113, 4, to_wstring(score), 15);

        //Level
        DrawString(105, 6, wlevel, 15);
        DrawString(112, 6, to_wstring(level), 15);


        //Rysowanie statku
        DrawTriangle(ship->Playerx1(), ship->Playery1(), ship->Playerx2(), ship->Playery2(), ship->Playerx3(), ship->Playery3(), L'#', 14);
        FillTriangle(ship->Playerx1(), ship->Playery1(), ship->Playerx2(), ship->Playery2(), ship->Playerx3(), ship->Playery3(), L'#', 14);

        

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
        
        for(int which = 0; which < ile; which++)
        if (kosmita[which]->Kosmitax(0) < 1.5f && kosmita[which]->Shootable() == true)
        {
            for (int i = 0; i < ile; i++)
                    kosmita[i]->Kosmitay_wdol(1.0f);

            ruchwlewo = false;
        }
        
        for (int which = 0; which < ile; which++)
        if (kosmita[which]->Kosmitax(3) > 118.0f && kosmita[which]->Shootable() == true)
        {
            for (int i = 0; i < ile; i++)
                    kosmita[i]->Kosmitay_wdol(1.0f);

            ruchwlewo = true;
        }

        //Pomoc przy kolizji
        /*
        string1 = to_wstring(kosmita[0]->Kosmitay(0));
        DrawString(10, 21, string1, 15);
        string1 = to_wstring(pociskgracz->Pociskx());
        DrawString(10, 22, string1, 164);
        */

        //Kolizja kosmita
        for (int which = 0; which < ile; which++)
        {
                    if ((pociskgracz->Pociskx() >= kosmita[which]->Kosmitax(0) - 1.0f && pociskgracz->Pociskx() <= kosmita[which]->Kosmitax(3)+ 1.0f ) && (pociskgracz->Pocisky() >= kosmita[which]->Kosmitay(0)+ 1.0f && pociskgracz->Pocisky() <= kosmita[which]->Kosmitay(3)+ 1.0f ) && kosmita[which]->Shootable() == true)
                    {
                        pociskgracz->Pocisky(64.0f);
                        wystrzelony = false;
                        kosmita[which]->Kosmitaznak(NULL);
                        kosmita[which]->Kosmitacolor(NULL);
                        kosmita[which]->Shootable_zmien();
                        score += 100;
                        trafionych++;
                    }
                    if (trafionych == ile)
                    {
                        for (int ktory = 0; ktory < ile; ktory++)
                            kosmita[ktory]->Kosmita_poczatek();
                        
                        trafionych = 0; 
                        ruchwlewo = true;
                        level++;
                    }
        }

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
        

        //Rysowanie obramowania
        for (int i = 0; i < 70; i++)
            for (int j = 0; j < 120; j++)
                if (i == 0 || j == 0 || i == m_nScreenHeight - 1 || j == m_nScreenWidth - 1) Draw(j, i, L'#', 15);

        return true;
    }
};




int main()
{
    Gra gierka;
    gierka.ConstructConsole(120, 70, 10, 10);
    gierka.Start();

    system("PAUSE");
    return 0;
}