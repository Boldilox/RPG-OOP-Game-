// Knight.hpp
#pragma once
#include "Entity.hpp"
#include<vector>
#include <SDL_mixer.h>




class Knight : public Entity {
public:
    void update(float deltaTime);//to update current changes to knight.
    Knight(float p_x, float p_y, SDL_Texture* p_tex,Mix_Chunk* stepsound);
    void moveLeft(std::vector<Entity>& platforms);
    void moveRight(std::vector<Entity>& platforms);
    void setPosition(float p_x, float p_y); // Add the setPosition method will come handy later as combatsystem will have to spawn knight where itleft off.
    void jump();//function to handle jump event
    void applyGravity(std::vector<Entity>& platforms);//simulate gravity to bring knight back to the ground
    void decreasehealth(int dmg);
    int gethealth(); 
    void sethealth(int h);
    bool checkenemyspawn(std::vector<Entity>& platforms);
    // void slash(Enemy& enemy);
    
private:
    bool isTakingDamage;
    float damageAnimationTime;
    bool isCriticalHealth;//

    Mix_Chunk* step;
    float movementSpeed;
    float velocityY; //will help in jump function for the knight
    bool isJumping; //flag to check if knight is suspended in air or not(jumping or not)
    int health; // health of player
    bool checkCollisionWithPlatform(Entity& platform); //differentiatinig collision from gravity so i can check for movement left and right as well.

};
