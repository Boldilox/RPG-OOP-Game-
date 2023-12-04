#pragma once
#include "Enemy.hpp"
#include <SDL.h>

class Skeleton:public Enemy{
    public:
    Skeleton(float p_x , float p_y , SDL_Texture* p_tex , int h, int p);
    
};
