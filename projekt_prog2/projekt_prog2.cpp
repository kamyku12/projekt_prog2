#include <iostream>
#include "olcConsoleGameEngine.h"
using namespace std;

class Statek
{
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
        if (playerx3 < 160)
        {
            playerx1 += 30.0f * fElapsedTime;
            playerx2 += 30.0f * fElapsedTime;
            playerx3 += 30.0f * fElapsedTime;
        }
    }

    float playerx1;
    float playery1;
    float playerx2;
    float playery2;
    float playerx3;
    float playery3;
    int lifes;
};


class Gra : public olcConsoleGameEngine
{
private:
    Statek ship;
public:
    Gra()
    {}

    virtual bool OnUserCreate()
    {
        return true;
    }

    virtual bool OnUserUpdate(float fElapsedTime)
    {
        if (m_keys[VK_LEFT].bHeld) ship.Move_left(fElapsedTime);
        if (m_keys[VK_RIGHT].bHeld) ship.Move_right(fElapsedTime);


        for (int i = 0; i < 80; i++)
            for (int j = 0; j < 160; j++)
                if (i == 0 || j == 0 || i == m_nScreenHeight - 1 || j == m_nScreenWidth - 1) Draw(j, i, L'#', 15);
                else Draw(j, i, L' ', 0);

        DrawTriangle(ship.playerx1,ship.playery1,ship.playerx2,ship.playery2,ship.playerx3,ship.playery3,L'#',14);
        FillTriangle(ship.playerx1,ship.playery1,ship.playerx2,ship.playery2,ship.playerx3,ship.playery3,L'#',14);

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

