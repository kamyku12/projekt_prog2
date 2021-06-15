#include <iostream>
#include "olcConsoleGameEngine.h"
#include <cstdlib>
#include "Statek.h"
#include "Kosmita.h"
#include "Pocisk.h"
#include <vector>


class Gra : public olcConsoleGameEngine
{
private:
    Statek* ship;
    std::vector<Kosmita> kosmici;
    //Kosmita *kosmici[12];
    int score, ile;
    std::wstring wscore, wlevel, wzycia ,string1;
    int randomowa, randomowa2, level, trafionych;
    std::chrono::duration<float> elaps;
    std::chrono::system_clock::time_point cp1, cp2;
public:
    Gra()
    {
        srand(time(NULL));
        ile = 12;
        for (int i = 0; i < ile; i++)
        {
            randomowa = rand() % 5 + 0;
            randomowa2 = rand() % 5 + 1;
            kosmici.push_back(Kosmita(i, randomowa, randomowa2));
        }
        ship = new Statek;
        score = 0;
        level = 1;
        wscore = L"Score: ";
        wlevel = L"Level: ";
        wzycia = L"Lifes: ";
        trafionych = 0;
        cp1 = std::chrono::system_clock::now();
        cp2 = std::chrono::system_clock::now();
    }

    ~Gra()
    {
        delete ship;
        kosmici.clear();
    }

    bool OnUserCreate()
    {
        return true;
    }

    bool OnUserUpdate(float fElapsedTime)
    {
        //Zliczenie ile czasu trwa gra, glownie uzywany do wystrzalu kosmity
        cp2 = std::chrono::system_clock::now();
        elaps = elaps + (cp2 - cp1);
        cp1 = cp2;
        if (elaps.count() > 5.5) elaps = elaps.zero();
        float elaps2 = elaps.count();
        


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
        DrawString(113, 2, std::to_wstring(score), 15);

        DrawString(105, 4, wlevel, 15);
        DrawString(112, 4, std::to_wstring(level), 15);

        DrawString(105, 6, wzycia, 15);
        DrawString(112, 6, std::to_wstring(ship->Lifes()), 15);
        //-------------------------------------------


        //Rysowanie statku
        DrawTriangle(ship->Playerx(1), ship->Playery(1), ship->Playerx(2), ship->Playery(2), ship->Playerx(3), ship->Playery(3), L'#', 14);
        FillTriangle(ship->Playerx(1), ship->Playery(1), ship->Playerx(2), ship->Playery(2), ship->Playerx(3), ship->Playery(3), L'#', 14);
        //-------------------------------------------

        

        //Rysowanie Kosmity
        for (int which = 0; which < kosmici.size(); which++)
        {
            for (int x = 0; x < kosmici[which].Szerokosc(); x++)
                for (int y = 0; y < kosmici[which].Wysokosc(); y++)
                    if ((x >= 1 && x <= 3) && (y >=1 && y <= 3)) Draw(kosmici[which].Kosmitax(x), kosmici[which].Kosmitay(y), kosmici[which].Kosmita_znak_sr(), kosmici[which].Kosmita_color_sr());
                    else Draw(kosmici[which].Kosmitax(x), kosmici[which].Kosmitay(y), kosmici[which].Kosmita_znak(), kosmici[which].Kosmita_color());

        }
        //-------------------------------------------
        
        //Ruch Kosmity
        for (int which = 0; which < kosmici.size(); which++)
        {
            kosmici[which].Move(fElapsedTime, level);
        }
        
        for(int which = 0; which < kosmici.size(); which++)
        if (kosmici[which].Kosmitax(0) < 1.5f && kosmici[which].Shootable() == true)
        {
            for (int ktory = 0; ktory < kosmici.size(); ktory++)
            {
                kosmici[ktory].Kosmitay_wdol(1.0f);
                kosmici[ktory].Ruch_w_lewo(false);
            }
        }
        
        for (int which = 0; which < kosmici.size(); which++)
        if (kosmici[which].Kosmitax(3) > 118.0f && kosmici[which].Shootable() == true)
        {
            for (int ktory = 0; ktory < kosmici.size(); ktory++)
            {
                    kosmici[ktory].Kosmitay_wdol(1.0f);
                    kosmici[ktory].Ruch_w_lewo(true);
            }
        }
        //-------------------------------------------


        //Kolizja pocisku z kosmita
        for (int which = 0; which < kosmici.size(); which++)
        {
                    if ((ship->Pociskx() >= kosmici[which].Kosmitax(0) - 1.0f && ship->Pociskx() <= kosmici[which].Kosmitax(4)+ 1.0f ) && (ship->Pocisky() >= kosmici[which].Kosmitay(0)+ 1.0f && ship->Pocisky() <= kosmici[which].Kosmitay(4)+ 1.0f ) && kosmici[which].Shootable() == true)
                    {
                        ship->Pocisky(0.0f);
                        ship->Wystrzelony(false);
                        kosmici[which].Kosmita_znak(NULL);
                        kosmici[which].Kosmita_color(NULL);
                        kosmici[which].Shootable_zmien();
                        if (kosmici[which].Kosmita_znak() == L'A') score += 100;
                        trafionych++;
                    }
                    if (trafionych == kosmici.size())
                    {
                        for (int ktory = 0; ktory < kosmici.size(); ktory++)
                        {

                            kosmici[ktory].Kosmita_poczatek();
                            kosmici[ktory].Ruch_w_lewo(true);
                        }
                        trafionych = 0; 
                        level++;
                    }
        }
        //-------------------------------------------

        //Kolizja pocisku ze statkiem
        for (int which = 0; which < kosmici.size(); which++)
        {
            if (kosmici[which].Pociskx() >= ship->Playerx(2) - 0.5f && kosmici[which].Pociskx() <= ship->Playerx(3) + 0.5f && kosmici[which].Pocisky() >= ship->Playery(1))
            {
                kosmici[which].Pociskx(kosmici[which].Kosmitax(2));
                kosmici[which].Pocisky(kosmici[which].Kosmitay(2));
                ship->Life_minus();
                for (int ktory = 0; ktory < kosmici.size(); ktory++)
                {
                    kosmici[ktory].Kosmita_poczatek();
                    kosmici[ktory].Ruch_w_lewo(true);
                }
                trafionych = 0;
            }
        }
        //-------------------------------------------

        //Kosmici dochodza do poziomu gracza
        for (int which = 0; which < kosmici.size(); which++)
        {
            if (kosmici[which].Kosmitay(3) >= ship->Playery(1) || kosmici[which].Kosmitay(2) >= ship->Playery(1) && kosmici[which].Shootable() == true)
            {
                ship->Life_minus();
                for (int ktory = 0; ktory < kosmici.size(); ktory++)
                {
                    kosmici[ktory].Kosmita_poczatek();
                    kosmici[ktory].Ruch_w_lewo(true);
                }
                trafionych = 0;
            }
        }
        //-------------------------------------------

        //Rysowanie pocisku, ruch pocisku
        if (m_keys[VK_SPACE].bPressed && ship->Wystrzelony() == false)
        {
            ship->Wystrzelony(true);
            ship->Pociskx(ship->Playerx(1));
            ship->Pocisky(ship->Playery(1) - 1);
        }

        if (ship->Wystrzelony() == true)
        {

            Draw(ship->Pociskx(), ship->Pocisky(), L'O', 15);
            ship->Move_up(fElapsedTime);
            if (ship->Pocisky() <= 2.0f || (ship->Pociskx() >= 100.0f && ship->Pocisky() <= 10.0f))
            {
                ship->Pocisky(0.0f);
                ship->Pociskx(ship->Playerx(1));
                ship->Wystrzelony(false);
            }
        }
        //-------------------------------------------
        
        //Wystrzal kosmity
        for (int which = 0; which < kosmici.size(); which++)
        {
            //Strzelanie kosmitow z gornego rzedu
            if(which <= 5 && kosmici[which].Kosmitay(4) + 5 != kosmici[which + 6].Kosmitay(0) && kosmici[which+6].Shootable() == false && kosmici[which].Shootable() == true && kosmici[which].Shoot(elaps2) && kosmici[which].wystrzelony() == false)
            {
                kosmici[which].wystrzelony(true);
                kosmici[which].Pociskx(kosmici[which].Kosmitax(2));
                kosmici[which].Pocisky(kosmici[which].Kosmitay(4)+1);
            }
            
            //Strzelanie kosmitow z dolnego rzedu (nie musza sprawdzac czy ktos jest pod nimi)
            if (which > 5 && kosmici[which].Shootable() == true && kosmici[which].Shoot(elaps2) && kosmici[which].wystrzelony() == false)
            {
                kosmici[which].wystrzelony(true);
                kosmici[which].Pociskx(kosmici[which].Kosmitax(2));
                kosmici[which].Pocisky(kosmici[which].Kosmitay(4)+1);
            }
        }
        for (int which = 0; which < kosmici.size(); which++)
        {
            if (kosmici[which].wystrzelony() == true)
            {
                Draw(kosmici[which].Pociskx(), kosmici[which].Pocisky(), L'O', 5);
                kosmici[which].Move_down(fElapsedTime/2);
                if (kosmici[which].Pocisky() >= 69.0f)
                {
                    kosmici[which].wystrzelony(false);
                    kosmici[which].Pociskx(kosmici[which].Kosmitax(2));
                    kosmici[which].Pocisky(kosmici[which].Kosmitay(4)+1);
                    
                }
            }
        }

        //Rysowanie obramowania
        for (int i = 0; i < 70; i++)
            for (int j = 0; j < 120; j++)
                if (i == 0 || j == 0 || i == m_nScreenHeight - 1 || j == m_nScreenWidth - 1) Draw(j, i, L'#', 15);
        //-------------------------------------------


        //Jesli nie masz zyc, przegrywasz
        if (ship->Lifes() == 0)
        {
            for (int i = 0; i < 70; i++)
                for (int j = 0; j < 120; j++)
                    Draw(j, i, L' ', 0);

            DrawString(m_nScreenWidth / 2 - 26, m_nScreenHeight / 2, L"Przegrałeś, nacisnij dowolny przycisk aby zakonczyc", 15);

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
            DrawString(m_nScreenWidth / 2 + 1, m_nScreenHeight / 2 + 1, std::to_wstring(score), 15);
            DrawString(m_nScreenWidth / 2 - 17, m_nScreenHeight / 2 + 2, L"Nacisnij dowolny przycisk aby zakończyć", 15);

            return false;
        }

        //Pomoc przy kolizji
        /*string1 = to_wstring(elaps2);
        DrawString(10, 21, string1, 15);
        string1 = to_wstring(kosmita[0]->Pocisky());
        DrawString(10, 22, string1, 15);*/

        return true;
    }
};




int main()
{
    Gra Invaders;
    Invaders.ConstructConsole(120, 70, 10, 10);
    Invaders.Start();

    getchar();
    return 0;
}