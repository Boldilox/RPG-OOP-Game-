// Knight.cpp
#include "Knight.hpp"

Knight::Knight(float p_x, float p_y, SDL_Texture* p_tex) : Entity(p_x, p_y, p_tex) {
    movementSpeed = 0.1f;
}

void Knight::moveLeft() {
    x -= movementSpeed;
}

void Knight::moveRight() {
    x += movementSpeed;
}

void Knight::setPosition(float p_x, float p_y) {
    x = p_x;
    y = p_y-;
}
