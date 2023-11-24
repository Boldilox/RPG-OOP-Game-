#pragma once
#include "Entity.hpp"

class Enemy : public Entity {
    private:
    int health;
    int pwr;

    public:

    void attackKnight(Knight& knight);
    

};