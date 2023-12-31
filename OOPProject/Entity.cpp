#include "Entity.hpp"
#include<iostream>
#include <SDL.h>
#include <SDL_image.h>

Entity::Entity(float p_x , float p_y,SDL_Texture* p_tex):x(p_x),y(p_y),tex(p_tex){
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 128;
    currentFrame.h = 128;
}

float Entity::getX(){
    return x;
}

float Entity::getY(){
    return y;
}

SDL_Texture* Entity::getTex(){
    return tex;
}

SDL_Rect Entity::getCurrentFrame(){
    return currentFrame;
}

void Entity::change_src(float _x, float _y, float width, float height) {
    currentFrame.x = _x;
    currentFrame.y = _y;
    currentFrame.w = width;
    currentFrame.h = height;
}

