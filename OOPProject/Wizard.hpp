#pragma once
#include <SDL.h>
#include "Enemy.hpp"

class Wizard:public Enemy{
    public:
    Wizard(float p_x, float p_y, SDL_Texture* p_tex,int h,int p);
    
};