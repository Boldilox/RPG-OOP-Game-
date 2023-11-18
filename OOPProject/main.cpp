#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Knight.hpp" // Include the Knight class header

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cout << "Hey..SDL_Init has failed. SDL ERROR: " << SDL_GetError() << std::endl;
    }

    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cout << "IMG_Init has failed. Error" << SDL_GetError() << std::endl;
    }

    RenderWindow window("Game", 1280, 720);

    SDL_Texture* cavegroundTexture = window.loadTexture("res/gfx/ground_cave.png");
    SDL_Texture* knightTexture = window.loadTexture("res/gfx/KnightSprite.png");

    std::vector<Entity> platforms;
    int x = 0;
    int y = 592;

    for (int i = 0; i < 10; i++) {
        platforms.push_back(Entity(x, y, cavegroundTexture));
        x += 128;
    }

    // Create the knight object
    Knight knight(0, 0, knightTexture); // Initial position (0, 0) - adjust as needed

    // Assuming the knight spawns on the left side of the first platform
    float knightInitialX = platforms[0].getX(); // Adjust as needed
    float knightInitialY = platforms[0].getY() - knight.getCurrentFrame().h+64; // Adjust as needed

    knight.setPosition(knightInitialX, knightInitialY); // Set knight's position

    bool gameRunning = true;
    SDL_Event event;

    while (gameRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameRunning = false;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            knight.moveLeft(); // Move the knight left based implementation
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            knight.moveRight(); // Move the knight right based implementation
        }
        if (currentKeyStates[SDL_SCANCODE_UP]){
            knight.jump();
        }
        
        knight.applyGravity(platforms);

        window.clear();

        for (int i = 0; i < 10; i++) {
            window.render(platforms[i]);
        }

        // Render the knight after movement
        window.render(knight);

        window.display();
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}
