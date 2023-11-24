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
    //SDL_Texture* wizardTexture = window.loadTexture("res/gfx/wizard.png"); furture ayaan uncomment this when the enemy clss is implemented properly
    //NEED TO IMPLEMENT BUSHES FOR ENEMY

    //NEED TO IMPLEMENT ENEMY VARIABLE SO I CAN CALL THAT IN COMBAT SYSTEM
    //make health while you are at it as well future ayaan :)

    std::vector<Entity> platforms;
    int x = 0;
    int y = 592;

    for (int i = 0; i < 10; i++) {
        platforms.push_back(Entity(x, y, cavegroundTexture));
        x += 128;
    }

    // Create the knight object
    Knight knight(0, 0, knightTexture); // Initial position (0, 0) - adjust as needed
    // Wizard wizard(672 , 0 , WizardTexture );

    // Assuming the knight spawns on the left side of the first platform
    float knightInitialX = platforms[0].getX(); // Adjust as needed
    float knightInitialY = platforms[0].getY() - knight.getCurrentFrame().h+64; // Adjust as needed

    knight.setPosition(knightInitialX, knightInitialY); // Set knight's position

    bool gameRunning = true;
    SDL_Event event;
    bool isInCombat=false;
    bool combatRunning = false;
    RenderWindow* combatWindow;
    SDL_Event combatEvent;
    
    
    while (gameRunning) {
        SDL_Delay(15);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                std::cout<<"aa rehay hain"<<std::endl;
                if(combatRunning){
                    combatRunning = false;
                    isInCombat = false;
                    combatWindow->cleanUp();
                    delete combatWindow;
                }
                else{
                    gameRunning = false;
                    }
                
            }
        }
       
    
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_A]) {
            knight.moveLeft(); // Move the knight left based implementation
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            knight.moveRight(); // Move the knight right based implementation
        }
        if (currentKeyStates[SDL_SCANCODE_W]){
            knight.jump();
        }
        
        knight.applyGravity(platforms);
        

        window.clear();

        if (currentKeyStates[SDL_SCANCODE_K]) {
            isInCombat = true;

            // Open combat window
            combatWindow = new RenderWindow("Combat", 800, 450);
            combatRunning = true;
            
           
        }
        if (combatRunning) {
            combatWindow->clear();
            combatWindow->display();
        }
        

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
