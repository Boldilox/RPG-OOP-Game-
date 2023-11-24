// Knight.hpp
#pragma once
#include "Entity.hpp"
#include<vector>


class Knight : public Entity {
public:
    Knight(float p_x, float p_y, SDL_Texture* p_tex);
    void moveLeft();
    void moveRight();
    void setPosition(float p_x, float p_y); // Add the setPosition method will come handy later as combatsystem will have to spawn knight where itleft off.
    void jump();//function to handle jump event
    void applyGravity(std::vector<Entity>& platforms);//simulate gravity to bring knight back to the ground
    void decreasehealth(int health);
private:
    
    float movementSpeed;
    float velocityY; //will help in jump function for the knight
    bool isJumping; //flag to check if knight is suspended in air or not(jumping or not)
    int health; // health of player

};
