#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Entity{

    public:
        Entity(float p_x,float p_y,SDL_Texture* p_tex);
        
        float getX();
        float getY();
        SDL_Texture* getTex();
        SDL_Rect getCurrentFrame();
        virtual ~Entity(){}
        void change_src(float _x, float _y, float width, float height);
    protected:
        float x, y;
        
        SDL_Rect currentFrame;
        SDL_Texture* tex;


};