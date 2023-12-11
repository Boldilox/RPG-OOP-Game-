// Knight.cpp
#include "Knight.hpp"


Knight::Knight(float p_x, float p_y, SDL_Texture* p_tex, Mix_Chunk* stepsound) : Entity(p_x, p_y, p_tex),step(stepsound){
    change_src(22,0,128,128);
    movementSpeed = 5.0f;
    isJumping = false;
    velocityY=0.0f;
    health = 200;
    isTakingDamage = false;
    damageAnimationTime = 0.0f;
   

}

void Knight::decreasehealth(int dmg){
    health -= dmg;
    isTakingDamage = true;
    damageAnimationTime = 0.0f; // Reset animation timer
    // Set the initial frame for damage animation
    change_src(322,0,128,128); //DAMAGE SPRITE COORDS COME HERE
}

int Knight::gethealth(){
    return health;
}

void Knight::sethealth(int h){
    health = h;
}
void Knight::moveLeft(std::vector<Entity>& platforms) {
    // Move the knight left
    x -= movementSpeed;

    if (x < 0) {
        x = 0; // Set the left boundary
    }
    
    // Check for collisions with platforms after moving
    for (int i = 0; i < platforms.size(); i++) {
        if (checkCollisionWithPlatform(platforms[i])) {
            // Adjust horizontal position to prevent passing through the platform
            x = platforms[i].getX() + platforms[i].getCurrentFrame().w;
        }
    }
    if(!isJumping){
        if (Mix_Playing(-1) == 0) { // Replace -1 with the specific channel number if needed
            // Play sound when moving left
            Mix_PlayChannel(-1, step, 0);
        }
    }
    change_src(172 , 0 , 128 ,128);
}

void Knight::moveRight(std::vector<Entity>& platforms) {
    // Move the knight right
    x += movementSpeed;
    change_src(22,0,128,128);
    // Check and adjust the knight's position if it's out of the screen bounds
    if (x>1216){
        x=1216;
    }


    // Check for collisions with platforms after moving
    for (int i = 0; i < platforms.size(); i++) {
        if (checkCollisionWithPlatform(platforms[i])) {
            // Adjust horizontal position to prevent passing through the platform
            x = platforms[i].getX() - getCurrentFrame().w + 64;
        }
    }

    if(!isJumping){
        if (Mix_Playing(-1) == 0) { // Replace -1 with the specific channel number if needed
            // Play sound when moving left
            Mix_PlayChannel(-1, step, 0);
        }
    }
}

void Knight::setPosition(float p_x, float p_y) {
    x = p_x;
    y = p_y;
}

void Knight::jump() {
    if (!isJumping) {
        velocityY = -13.0f; // velocity of jump can be adjusted
        isJumping = true;   // set flag to check jumping or not
    }
}

void Knight::applyGravity(std::vector<Entity>& platforms) {
    if (y < 592) {
        velocityY += 0.6f; // gravity force
        float originalY = y; // Store original y position

        y += velocityY;

        bool collided = false;
        for (int i = 0; i < platforms.size(); i++) {
            if (checkCollisionWithPlatform(platforms[i])) {
                collided = true;

                // Adjust knight's position based on collision direction
                if (velocityY > 0) { // Knight is moving downwards
                    y = platforms[i].getY() - getCurrentFrame().h;
                    isJumping = false;
                    velocityY = 0.0f;
                } else if (velocityY < 0) { // Knight is moving upwards
                    y = platforms[i].getY() + platforms[i].getCurrentFrame().h -64;
                    velocityY = 0.0f;
                }
                break;
            }
        }

        if (!collided) {
            isJumping = true;
        }
    } else {
        isJumping = false;
        velocityY = 0.0f;
        y = 592;
    }
}

// void Knight::slash(Enemy& enemy){
//     enemy.decreasehealth(20);
// }

bool Knight::checkCollisionWithPlatform(Entity& platform) { //collision is now out of the apply graivty function for further use.
    return (y + getCurrentFrame().h > platform.getY() &&
            y < platform.getY() + platform.getCurrentFrame().h-64 &&
            x + (getCurrentFrame().w - 64) > platform.getX() &&
            x < platform.getX() + platform.getCurrentFrame().w);
            
}

bool Knight::checkenemyspawn(std::vector<Entity>& platforms){
    for (int i;i < platforms.size(); i++){
        if(checkCollisionWithPlatform(platforms[i])){
            return true;
        }
    }
    return false;
}