// Knight.hpp
#pragma once
#include "Entity.hpp"

class Knight : public Entity {
public:
    Knight(float p_x, float p_y, SDL_Texture* p_tex);
    void moveLeft();
    void moveRight();
    void setPosition(float p_x, float p_y); // Add the setPosition method will come handy later as combatsystem will have to spawn knight where itleft off.
private:
    float movementSpeed;
};
