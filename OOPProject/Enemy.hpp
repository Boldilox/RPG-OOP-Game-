#pragma once
#include <iostream>
#include "Entity.hpp"
#include "Knight.hpp"

class Enemy : public Entity {
    protected:
    int pwr;
    int health;

    public:
    Enemy(float p_x , float p_y , SDL_Texture* p_tex,int h,int p);

    void attackKnight(Knight& knight);
    virtual ~Enemy(){};
    virtual void decreasehealth(int dmg);
    virtual int gethealth();
    virtual void sethealth(int x);

};