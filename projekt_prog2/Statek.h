#pragma once

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

    void Move_left(float fElapsedTime);
    void Move_right(float fElapsedTime);
    float Playerx1();
    float Playerx2();
    float Playerx3();
    float Playery1();
    float Playery2();
    float Playery3();
};