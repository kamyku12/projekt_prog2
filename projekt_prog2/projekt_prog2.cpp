#include <iostream>
#include "olcConsoleGameEngine.h"
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
        playerx1 = 80.0f;
        playery1 = 75.0f;
        playerx2 = 77.0f;
        playery2 = 78.0f;
        playerx3 = 83.0f;
        playery3 = 78.0f;
        lifes = 3;
    }

    void Move_left(float fElapsedTime)
    {
        if (playerx2 > 2.0f)
        {
            playerx1 -= 30.0f * fElapsedTime;
            playerx2 -= 30.0f * fElapsedTime;
            playerx3 -= 30.0f * fElapsedTime;
        }
    }

    void Move_right(float fElapsedTime)
    {
        if (playerx3 < 160.0f)
        {
            playerx1 += 30.0f * fElapsedTime;
            playerx2 += 30.0f * fElapsedTime;
            playerx3 += 30.0f * fElapsedTime;
        }
    }
    int Playerx1() { return playerx1; }
    int Playerx2() { return playerx2; }
    int Playerx3() { return playerx3; }
    int Playery1() { return playery1; }
    int Playery2() { return playery2; }
    int Playery3() { return playery3; }
};

class Pocisk
{
public:
    float pocisky;
    bool up;
    Pocisk()
    {
        pocisky = 74.0f;
        up = true;
    }

    void Move_up(float fElapsedTime)
    {
        if (up == true && pocisky > 2.0f) pocisky -= 30.0f * fElapsedTime;
    }

    void Move_down(float fElapsedTime)
    {
        if (up == false) pocisky += 30.0f * fElapsedTime;
    }
};


class Gra : public olcConsoleGameEngine
{
private:
    Statek *ship = new Statek;
    Pocisk *pociskgracz = new Pocisk;
    int pociskx;
    bool wystrzelony;
public:
    Gra()
    {}

    virtual bool OnUserCreate()
    {
        wystrzelony = false;
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
        DrawTriangle(ship->Playerx1(),ship->Playery1(),ship->Playerx2(),ship->Playery2(),ship->Playerx3(),ship->Playery3(),L'#',14);
        FillTriangle(ship->Playerx1(),ship->Playery1(),ship->Playerx2(),ship->Playery2(),ship->Playerx3(),ship->Playery3(),L'#',14);

        //Rysowanie pocisku, ruch pocisku
        if (m_keys[VK_SPACE].bPressed)
        {
            wystrzelony = true;
            pociskx = ship->Playerx1();
        }

        if (wystrzelony == true)
        {
            Draw(pociskx, pociskgracz->pocisky, L'o', 5);
            pociskgracz->Move_up(fElapsedTime);
            if (pociskgracz->pocisky <= 2.0f)
            {
                pociskgracz->pocisky = 74.0f;
                pociskx = ship->Playerx1();
                wystrzelony = false;
            }
        }
        return true;
    }
};




int main()
{
    Gra gierka;
    gierka.ConstructConsole(160, 80, 8, 8);
    gierka.Start();

    system("PAUSE");
    return 0;
}

