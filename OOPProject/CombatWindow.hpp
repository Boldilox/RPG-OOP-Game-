
#pragma once

#include <iostream>
#include <SDL.h>
#include<SDL_image.h>
#include "Knight.hpp"

#include "Entity.hpp"
class CombatWindow {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:

    CombatWindow(const char* p_title,int p_W,int p_h);
    void render(Entity& p_entity);
    void destroy();
    SDL_Texture* loadTexture(const char* p_filePath);
    void display();
    
};