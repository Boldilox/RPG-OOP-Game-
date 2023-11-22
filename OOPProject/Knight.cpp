// Knight.cpp
#include "Knight.hpp"

Knight::Knight(float p_x, float p_y, SDL_Texture* p_tex) : Entity(p_x, p_y, p_tex) {
    movementSpeed = 5.0f;
    isJumping = false;
    velocityY=0.0f;
}

void Knight::moveLeft() {
    x -= movementSpeed;
}

void Knight::moveRight() {
    x += movementSpeed;
}

void Knight::setPosition(float p_x, float p_y) {
    x = p_x;
    y = p_y;
}

void Knight::jump(){
    if(!isJumping){
        velocityY = -10.0f; //velocity of jump can be adjusted
        isJumping = true; //set flag to check jumping or not
    }
}

void Knight::applyGravity(std::vector<Entity>& platforms){
    if(y<592){//592 is the ground starting y value
        velocityY += 0.6f;//gravity force
        y+=velocityY; 

        
        //collision detection        
        for(int i = 0;i<platforms.size();i++){
            if(y + getCurrentFrame().h > platforms[i].getY()&&
               y < platforms[i].getY() + platforms[i].getCurrentFrame().h &&
               x + getCurrentFrame().w > platforms[i].getX() &&
               x < platforms[i].getX() + platforms[i].getCurrentFrame().w){
                //collision has occured
                y =platforms[i].getY() - getCurrentFrame().h;
                isJumping = false; //reset jumping flag
                velocityY = 0.0f;//vertical velocity set to none again
                
               

               }
        } 
    }
    else{
        isJumping = false; //reset jump flag
        velocityY = 0.0f; //velocity reset to zero
        y=592; //knight on ground
    }
}