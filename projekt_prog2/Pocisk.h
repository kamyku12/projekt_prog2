#pragma once

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

    void Move_up(float fElapsedTime);
    void Move_down(float fElapsedTime);

    float Pociskx();
    float Pocisky();
    void Pociskx(float x);
    void Pocisky(float y);
};