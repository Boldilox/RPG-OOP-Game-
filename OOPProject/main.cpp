#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Knight.hpp" // Include the Knight class header
#include "startscreen.hpp"
#include "Won.hpp"
#include "BG.hpp"
#include "Lost.hpp"


bool showStartScreen(RenderWindow& window) {
    SDL_Texture* startScreenTexture = window.loadTexture("res/gfx/startscreen.png");
    bool startGame = false;
    startscreen start(0,0,startScreenTexture);

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
            else if (event.type == SDL_KEYDOWN) {
                // Check for key presses to start the game (e.g., 'Enter/Return' key) we can change this as we like this.
                if (event.key.keysym.sym == SDLK_RETURN) {
                    startGame = true;
                    running = false;
                    break;
                }
            }
        }

        window.clear();
        // Render the start screen
        window.render(start);
        window.display();
    }

    SDL_DestroyTexture(startScreenTexture);
    return startGame;
}

bool Renderwinning(RenderWindow& window){
    SDL_Texture* wontexture = window.loadTexture("res/gfx/won_screen.png");
    bool wondone = false;
    Won winscreen(0,0,wontexture);

    SDL_Event wonevent ;
    bool running = true;
    while (running){
        while(SDL_PollEvent(&wonevent)){
            if(wonevent.type == SDL_QUIT){
                running = false;
                break;
            }
            else if(wonevent.type == SDL_KEYDOWN){
                if (wonevent.key.keysym.sym == SDLK_RETURN) {
                    wondone = true;
                    running = false;
                    break;
                }
            }
        }

        window.clear();
        window.render(winscreen);
        window.display();
    } 
    
    SDL_DestroyTexture(wontexture);
    return wondone;
}

bool RenderLosing(RenderWindow& window){
    SDL_Texture* losttexture = window.loadTexture("res/gfx/test.png");
    bool lostdone = false;
    Lost lostscreen(0,0,losttexture);

    SDL_Event lostevent ;
    bool running = true;
    while (running){
        while(SDL_PollEvent(&lostevent)){
            if(lostevent.type == SDL_QUIT){
                running = false;
                break;
            }
            else if(lostevent.type == SDL_KEYDOWN){
                if (lostevent.key.keysym.sym == SDLK_RETURN) {
                    lostdone = true;
                    running = false;
                    break;
                }
            }
        }

        window.clear();
        window.render(lostscreen);
        window.display();
    } 
    
    SDL_DestroyTexture(losttexture);
    return lostdone;
}


int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cout << "Hey..SDL_Init has failed. SDL ERROR: " << SDL_GetError() << std::endl;
    }

    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cout << "IMG_Init has failed. Error" << SDL_GetError() << std::endl;
    }

    RenderWindow window("Game", 1280, 720);

    bool startGame = showStartScreen(window);

    if (!startGame) {
        window.cleanUp();
        SDL_Quit();
        return 0;
    }
    

    SDL_Texture* cavegroundTexture = window.loadTexture("res/gfx/ground_cave.png");//caveground txture loading here
    SDL_Texture* knightTexture = window.loadTexture("res/gfx/KnightSprite.png");
    SDL_Texture* backgroundtexture = window.loadTexture("res/gfx/Background.png");
    SDL_Texture* testtexture = window.loadTexture("res/gfx/test.png");
    
    //SDL_Texture* wizardTexture = window.loadTexture("res/gfx/wizard.png"); furture ayaan uncomment this when the enemy clss is implemented properly
    //NEED TO IMPLEMENT BUSHES FOR ENEMY

    //NEED TO IMPLEMENT ENEMY VARIABLE SO I CAN CALL THAT IN COMBAT SYSTEM
    //make health while you are at it as well future ayaan :)

    std::vector<Entity> platforms;
    int x = 0;
    int y = 592;

    for (int i = 0; i < 10; i++) {
        platforms.push_back(Entity(x, y, cavegroundTexture)); //ground being made
        x += 128;
    }
    platforms.push_back(Entity(266,464,cavegroundTexture));//platforms to jump on
    platforms.push_back(Entity(0,400,cavegroundTexture));
    platforms.push_back(Entity(280,272,cavegroundTexture));
    platforms.push_back(Entity(398,272,cavegroundTexture));
    platforms.push_back(Entity(826,400,cavegroundTexture)); //tricky platform to land on hehe
    platforms.push_back(Entity(1082,292,cavegroundTexture));
    platforms.push_back(Entity(826,162,cavegroundTexture));
    platforms.push_back(Entity(1152,128,cavegroundTexture));

    BG Background(0,0,backgroundtexture);
    BG test(0,0,testtexture);
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
    bool combatRunning = true;
    bool won = false;
    bool lost = false;
    RenderWindow* combatWindow = nullptr; 
    bool savedPosition = false;
    float savedKnightX , savedKnightY;

    while (gameRunning) {
        SDL_Delay(15);
        if(!isInCombat){
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    // std::cout<<"aa rehay hain"<<std::endl;
                    gameRunning = false;
                }
                else if ((knight.getX() == 1152 || knight.getX()> 1152) && (knight.getY() == 0)){
                    gameRunning = false;
                    won = true;
                }
            }
            

            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            
            if (currentKeyStates[SDL_SCANCODE_C]) {
                if (!savedPosition) {
                    // Save knight's position only if it's not already saved
                    savedKnightX = knight.getX();
                    savedKnightY = knight.getY();
                    savedPosition = true;
                }
                
                isInCombat = !isInCombat; // Toggle combat mode
            }

            if (currentKeyStates[SDL_SCANCODE_A]) {
                knight.moveLeft(platforms); // Move the knight left based implementation
            }
            if (currentKeyStates[SDL_SCANCODE_D]) {
                knight.moveRight(platforms); // Move the knight right based implementation
            }
            if (currentKeyStates[SDL_SCANCODE_W]){
                knight.jump();
            }
            
            knight.applyGravity(platforms);
            

            window.clear();
            window.render(Background);

            for (int i = 0; i < platforms.size(); i++) {
                window.render(platforms[i]); //rendering all platforms 
            }

            // Render the knight after movement
            window.render(knight);

            window.display();
        }
        else if(isInCombat){
            SDL_Delay(30);
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    // std::cout<<"aa rehay hain"<<std::endl;
                    gameRunning = false;
                }
                else if(knight.gethealth()<=0){
                    isInCombat = false;
                    lost = true;
                    gameRunning = false;
                    savedPosition = false;
                }
            }
            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            if(currentKeyStates[SDL_SCANCODE_UP]){
                int randomn = rand()%3;
                std::cout<<randomn;
            }
            if(currentKeyStates[SDL_SCANCODE_DOWN]){

            }
            if(currentKeyStates[SDL_SCANCODE_LEFT]){

            }
            
            knight.setPosition(256,592);
            window.clear();
            window.render(knight);
            window.display();

            if(currentKeyStates[SDL_SCANCODE_K]){
                knight.decreasehealth(200);
            }
            // if(currentKeyStates[SDL_SCANCODE_I]){
            //     isInCombat = false;
            //     knight.setPosition(savedKnightX,savedKnightY);
            //     savedPosition = false;
            // }
            
        }
    }
    

    window.cleanUp();
    SDL_Quit();

    if(won){
        RenderWindow winningscreen("Success or so..", 1280 , 720);
        bool wongame = Renderwinning(winningscreen);
        if(!wongame){
        winningscreen.cleanUp();
        SDL_Quit();
        return 0;
        }
    }

    if(lost){
        RenderWindow losingscreen("You Suck",1280,720);
        bool lostgame = RenderLosing(losingscreen);
        if(!lostgame){
            losingscreen.cleanUp();
            SDL_Quit();
            return 0;
        }
    }

    return 0;

}