// Knight.cpp
#include "Knight.hpp"

Knight::Knight(float p_x, float p_y, SDL_Texture* p_tex) : Entity(p_x, p_y, p_tex) {
    movementSpeed = 5.0f;
    isJumping = false;
    velocityY=0.0f;
    health = 200;
}

void Knight::moveLeft(std::vector<Entity>& platforms) {
    // Move the knight left
    x -= movementSpeed;
    

    // Check for collisions with platforms after moving
    for (int i = 0; i < platforms.size(); i++) {
        if (checkCollisionWithPlatform(platforms[i])) {
            // Adjust horizontal position to prevent passing through the platform
            x = platforms[i].getX() + platforms[i].getCurrentFrame().w;
        }
    }
}

void Knight::moveRight(std::vector<Entity>& platforms) {
    // Move the knight right
    x += movementSpeed;

    // Check for collisions with platforms after moving
    for (int i = 0; i < platforms.size(); i++) {
        if (checkCollisionWithPlatform(platforms[i])) {
            // Adjust horizontal position to prevent passing through the platform
            x = platforms[i].getX() - getCurrentFrame().w + 64;
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


bool Knight::checkCollisionWithPlatform(Entity& platform) { //collision is now out of the apply graivty function for further use.
    return (y + getCurrentFrame().h > platform.getY() &&
            y < platform.getY() + platform.getCurrentFrame().h-64 &&
            x + (getCurrentFrame().w - 64) > platform.getX() &&
            x < platform.getX() + platform.getCurrentFrame().w);
            
}