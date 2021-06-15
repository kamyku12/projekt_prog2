#pragma once

class Pocisk
{
private:
    float pocisky, pociskx;
    bool up;
public:
    Pocisk();

    void Move_up(float fElapsedTime);
    void Move_down(float fElapsedTime);

    float Pociskx();
    float Pocisky();
    void Pociskx(float x);
    void Pocisky(float y);
};