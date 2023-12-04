#pragma once
#include <SDL.h>
#include "Enemy.hpp"

class Troll:public Enemy{
    public:
    Troll(float p_x, float p_y, SDL_Texture* p_tex,int h,int p);
    
};