#include <iostream>
#include "olcConsoleGameEngine.h"
#include <cstdlib>
#include "Statek.h"
#include "Kosmita.h"
#include "Pocisk.h"

using namespace std;


class Gra : public olcConsoleGameEngine
{
private:
    Statek* ship;
    bool wystrzelony, ruchwlewo;
    Kosmita *kosmita[12];
    int score, ile;
    wstring wscore, wlevel, wzycia ,string1;
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
        score = 0;
        level = 1;
        wscore = L"Score: ";
        wlevel = L"Level: ";
        wzycia = L"Lifes: ";
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
        //-------------------------------------------

        //Rysowanie pustego srodka
        for (int i = 0; i < 70; i++)
            for (int j = 0; j < 120; j++)
                if (i != 0 && j != 0 && i != m_nScreenHeight - 1 && j != m_nScreenWidth - 1) Draw(j, i, L' ', 0);
        //-------------------------------------------

        //Box na score
        for (int i = 0; i < 10; i++)
            for (int j = 100; j < 120; j++)
                if (i == 0 || j == 100 || i == 9 || j == 119) Draw(j, i, L'#', 15);
                else Draw(j, i, L' ', 0);
        //-------------------------------------------

        //level, zycia, score
        DrawString(105, 2, wscore, 15);
        DrawString(113, 2, to_wstring(score), 15);

        DrawString(105, 4, wlevel, 15);
        DrawString(112, 4, to_wstring(level), 15);

        DrawString(105, 6, wzycia, 15);
        DrawString(112, 6, to_wstring(ship->Lifes()), 15);
        //-------------------------------------------


        //Rysowanie statku
        DrawTriangle(ship->Playerx1(), ship->Playery1(), ship->Playerx2(), ship->Playery2(), ship->Playerx3(), ship->Playery3(), L'#', 14);
        FillTriangle(ship->Playerx1(), ship->Playery1(), ship->Playerx2(), ship->Playery2(), ship->Playerx3(), ship->Playery3(), L'#', 14);
        //-------------------------------------------

        

        //Rysowanie Kosmity
        for (int which = 0; which < ile; which++)
        {
            for (int x = 0; x < kosmita[which]->Szerokosc(); x++)
                for (int y = 0; y < kosmita[which]->Wysokosc(); y++)
                    if ((x == 1 || x == 2) && (y == 1 || y == 2)) Draw(kosmita[which]->Kosmitax(x), kosmita[which]->Kosmitay(y), kosmita[which]->Kosmitaznak_sr(), kosmita[which]->Kosmitacolor_sr());
                    else Draw(kosmita[which]->Kosmitax(x), kosmita[which]->Kosmitay(y), kosmita[which]->Kosmitaznak(), kosmita[which]->Kosmitacolor());
        }
        //-------------------------------------------
        
        //Ruch Kosmity
        for (int which = 0; which < ile; which++)
        {
           kosmita[which]->Move(fElapsedTime, ruchwlewo, level);
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
        //-------------------------------------------

        //Pomoc przy kolizji
        
        string1 = to_wstring(ship->Pocisky());
        DrawString(10, 21, string1, 15);
        string1 = to_wstring(ship->Pociskx());
        DrawString(10, 22, string1, 164);

        //Kolizja pocisku z kosmita
        for (int which = 0; which < ile; which++)
        {
                    if ((ship->Pociskx() >= kosmita[which]->Kosmitax(0) - 1.0f && ship->Pociskx() <= kosmita[which]->Kosmitax(3)+ 1.0f ) && (ship->Pocisky() >= kosmita[which]->Kosmitay(0)+ 1.0f && ship->Pocisky() <= kosmita[which]->Kosmitay(3)+ 1.0f ) && kosmita[which]->Shootable() == true)
                    {
                        ship->Pocisky(0.0f);
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
        //-------------------------------------------

        //Kosmici dochodza do poziomu gracza
        for (int which = 0; which < ile; which++)
        {
            if (kosmita[which]->Kosmitay(3) >= ship->Playery1() && kosmita[which]->Shootable() == true)
            {
                ship->Life_minus();
                for (int ktory = 0; ktory < ile; ktory++)
                    kosmita[ktory]->Kosmita_poczatek();

                trafionych = 0;
                ruchwlewo = true;
            }
        }
        //-------------------------------------------

        //Rysowanie pocisku, ruch pocisku
        if (m_keys[VK_SPACE].bPressed && wystrzelony == false)
        {
            wystrzelony = true;
            ship->Pociskx(ship->Playerx1());
            ship->Pocisky(ship->Playery1() - 1);
        }

        if (wystrzelony == true)
        {

            Draw(ship->Pociskx(), ship->Pocisky(), L'O', 15);
            ship->Move_up(fElapsedTime);
            if (ship->Pocisky() <= 2.0f || (ship->Pociskx() >= 100.0f && ship->Pocisky() <= 10.0f))
            {
                ship->Pocisky(0.0f);
                ship->Pociskx(ship->Playerx1());
                wystrzelony = false;
            }
        }
        //-------------------------------------------
        

        //Rysowanie obramowania
        for (int i = 0; i < 70; i++)
            for (int j = 0; j < 120; j++)
                if (i == 0 || j == 0 || i == m_nScreenHeight - 1 || j == m_nScreenWidth - 1) Draw(j, i, L'#', 15);
        //-------------------------------------------


        //Jesli nie masz juz zyc, przegrywasz
        if (ship->Lifes() == 0)
        {
            for (int i = 0; i < 70; i++)
                for (int j = 0; j < 120; j++)
                    Draw(j, i, L' ', 0);

            DrawString(m_nScreenWidth / 2 - 17, m_nScreenHeight / 2, L"Przegrałeś, nacisnij aby zakonczyc", 15);

            return false;
        }
        //-------------------------------------------

        if (level == 6)
        {
            for (int i = 0; i < 70; i++)
                for (int j = 0; j < 120; j++)
                    Draw(j, i, L' ', 0);

            DrawString(m_nScreenWidth / 2 - 17, m_nScreenHeight / 2, L"Gratulacje, wygrałeś", 15);
            DrawString(m_nScreenWidth / 2 - 17 + 1, m_nScreenHeight / 2 + 1, L"Zdobyte punkty: ", 15);
            DrawString(m_nScreenWidth / 2 + 1, m_nScreenHeight / 2 + 1, to_wstring(score), 15);

            return false;
        }

        return true;
    }
};




int main()
{
    Gra gierka;
    gierka.ConstructConsole(120, 70, 10, 10);
    gierka.Start();

    getchar();
    return 0;
}