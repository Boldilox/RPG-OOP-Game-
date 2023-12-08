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
#include "Enemy.hpp"
#include "Wizard.hpp"
#include "Skeleton.hpp"
#include "Moveset.hpp"
#include <SDL_mixer.h>
#include <thread>
#include <chrono>


Mix_Music *bgMusic = NULL;
Mix_Chunk *Block = NULL;
Mix_Chunk *stepsound = NULL;
Mix_Chunk *swordslash = NULL;
Mix_Chunk *shieldbash = NULL;
Mix_Chunk *headbutt = NULL;
Mix_Chunk *miss = NULL;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                return success;
}


bool loadMedia()
{
    bool success = true;
        // load the background music
        bgMusic = Mix_LoadMUS( "sounds/DIsc13.mp3" ); 
        Block = Mix_LoadWAV("sounds/Block.mp3");
        stepsound = Mix_LoadWAV("sounds/stepsound.wav");
        swordslash = Mix_LoadWAV("sounds/SwordSlash.mp3");
        shieldbash = Mix_LoadWAV("sounds/ShieldBash.mp3");
        headbutt = Mix_LoadWAV("sounds/Headbutt.mp3");
        miss = Mix_LoadWAV("sounds/missingsound.wav");

    if(bgMusic == NULL){
        printf("Unable to load music: %s \n", Mix_GetError());
        success = false;
    }

    return success;
}

bool showStartScreen(RenderWindow& window) { //startscreen shown
    SDL_Texture* startScreenTexture = window.loadTexture("res/gfx/startscreen.png");//load texture
    bool startGame = false;
    startscreen start(0,0,startScreenTexture); //make screen

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

bool Renderwinning(RenderWindow& window){//winnig screen will be shown if the won flag is true(similar to start screen code)
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

bool RenderLosing(RenderWindow& window){ //Losing screen done here for rendering a differnet losing window(similar to start screen code)
    SDL_Texture* losttexture = window.loadTexture("res/gfx/LoseScreen.png");
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

    if (!init()) {
        std::cerr << "Initialization failed." << std::endl;
        return 1;
    }

    if (!loadMedia()) {
        std::cerr << "Media loading failed." << std::endl;
        SDL_Quit();
        return 1;
    }


    RenderWindow window("Game", 1280, 720); //making main window here
   
    bool startGame = showStartScreen(window);

    if (!startGame) {
        window.cleanUp();
        SDL_Quit();
        return 0;
    }

    Mix_PlayMusic (bgMusic, -1);  // -1 to loop the music indefinitely
    SDL_Texture* cavegroundTexture = window.loadTexture("res/gfx/ground_cave.png");//caveground txture loading here
    SDL_Texture* knightTexture = window.loadTexture("res/gfx/KnightSpriteSheet.png");
    SDL_Texture* backgroundtexture = window.loadTexture("res/gfx/Background.png");
    SDL_Texture* testtexture = window.loadTexture("res/gfx/test.png");
    SDL_Texture* airplatform = window.loadTexture("res/gfx/airplatform.png"); //texture for platforms to jump to
    SDL_Texture* stonetexture = window.loadTexture("res/gfx/Stones.png"); //stone texture is added here
    SDL_Texture* movesettexture = window.loadTexture("res/gfx/MOVESET.png");
    


    std::vector<Entity> platforms;
    int x = 0;
    int y = 592;

    for (int i = 0; i < 10; i++) {
        platforms.push_back(Entity(x, y, cavegroundTexture)); //ground being made
        x += 128;
    }

    platforms.push_back(Entity(266,464,airplatform));//platforms to jump on
    platforms.push_back(Entity(0,400,airplatform));
    platforms.push_back(Entity(280,272,airplatform));
    platforms.push_back(Entity(398,272,airplatform));
    platforms.push_back(Entity(826,400,airplatform)); //tricky platform to land on hehe
    platforms.push_back(Entity(1082,292,airplatform));
    platforms.push_back(Entity(826,162,airplatform));
    platforms.push_back(Entity(1152,128,airplatform));

    std::vector<Entity> stones;
    int stonex = 640 ; 
    int stoney = 568;

    for (int i = 0; i < 6;i++){
        stones.push_back(Entity(stonex , stoney , stonetexture));
        stonex += 128;
    }

    stones.push_back(Entity(0,376,stonetexture));
    stones.push_back(Entity(826, 138 , stonetexture));

    

    BG Background(0,0,backgroundtexture);
    BG test(0,0,testtexture);
    // Create the knight object
    Knight knight(0, 0, knightTexture,stepsound); // Initial position (0, 0) - adjust as needed
    

    // Assuming the knight spawns on the left side of the first platform
    float knightInitialX = platforms[0].getX(); // Adjust as needed
    float knightInitialY = platforms[0].getY() - knight.getCurrentFrame().h+64; // Adjust as needed

    knight.setPosition(knightInitialX, knightInitialY); // Set knight's position
    Moveset moveset(0,0,movesettexture);

    bool gameRunning = true;
    SDL_Event event;
    bool isInCombat=false;
    bool combatRunning = true;
    bool won = false;
    bool lost = false;
    
    bool savedPosition = false;
    float savedKnightX , savedKnightY;
    bool enemyGenerated= false;
    float enemyX = 1152;
    float enemyY = 128;

    SDL_Texture* wizardtexture = window.loadTexture("res/gfx/Wizard.png");
    SDL_Texture* skeletontexture = window.loadTexture("res/gfx/Skeleton.png");

    Skeleton skeleton(enemyX,enemyY , skeletontexture, 40 ,1);
    Wizard wizard(enemyX , enemyY , wizardtexture, 60,2);
    std::vector<Enemy> enemies;
    enemies.push_back(skeleton);
    enemies.push_back(wizard);    
    int tofight;
    Uint32 starttime = SDL_GetTicks();
    Uint32 lastCollisionCheckTime = 0;//decalred for last collsion check so we can see 1 second for every iteration of the combat check
    Uint32 collisionCheckInterval = 1000; // Interval in milliseconds (1 seconds)
    int chancetofight = 0;

    while (gameRunning) {
        SDL_Delay(15);
        Uint32 currenttime = SDL_GetTicks();
        
        
        
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
            
            if (currenttime - lastCollisionCheckTime >= collisionCheckInterval){
                lastCollisionCheckTime = currenttime; 
                
                if (knight.checkenemyspawn(stones)) {
                    
                    chancetofight = rand()%10;
                    if(chancetofight >3){

                        
                        if (!savedPosition) {
                            // Save knight's position only if it's not already saved
                            savedKnightX = knight.getX();
                            savedKnightY = knight.getY();
                            savedPosition = true;
                        }
                        isInCombat = !isInCombat; // Toggle combat mode
                        tofight = rand()%2;
                        
                    }

                }
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
            for(int i = 0; i < stones.size(); i++){
                window.render(stones[i]);//rendering stones on platforms
            }

            // Render the knight after movement
            window.render(knight);

            window.display();
            
        }
        else if(isInCombat){
            Uint32 currenttime = SDL_GetTicks();
            lastCollisionCheckTime = currenttime; 
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
            knight.change_src(22,0,128,128);
            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            if(currentKeyStates[SDL_SCANCODE_L]){ //best attack technically but low damage
                SDL_Delay(100);
                int chance = rand()%7;
                if (chance<=5){ //85% chance attack will land

                    enemies[tofight].decreasehealth(15);
                    Mix_PlayChannel(-1 , headbutt ,0);
                }
                else{
                    Mix_PlayChannel(-1,miss , 0);
                }
                //15% chance you will miss hehe
                enemies[tofight].attackKnight(knight);

            }
            if(currentKeyStates[SDL_SCANCODE_J]){ //block mechanism for knight
                SDL_Delay(100);
                int checkblock = rand()%6;
                int currenthealth = knight.gethealth();

                if (checkblock <= 3){
                    enemies[tofight].attackKnight(knight);
                    knight.sethealth(currenthealth);
                    Mix_PlayChannel(-1 ,Block, 0);
                } 
                else if(checkblock>=3){
                    enemies[tofight].attackKnight(knight);
                    Mix_PlayChannel(-1 , miss ,0);
                }
            }
            if(currentKeyStates[SDL_SCANCODE_K]){  //50% chance attack but INSANE Damaege
                SDL_Delay(100);
                int chance = rand()%6;
                if(chance<=2){
                    enemies[tofight].decreasehealth(30);
                    Mix_PlayChannel(-1 , shieldbash ,0);
                }
                else{
                    Mix_PlayChannel(-1,miss,0);
                }
                enemies[tofight].attackKnight(knight);
            }
            if(currentKeyStates[SDL_SCANCODE_I]){ //100% attack hit rate but low damage
                SDL_Delay(100);
                enemies[tofight].decreasehealth(7);
                Mix_PlayChannel(-1,swordslash ,0);
                enemies[tofight].attackKnight(knight);
            }
            
            knight.setPosition(384,508); //set kight position to deafult fight
            window.clear();
            
            window.render(Background);
            window.render(knight);
            window.render(moveset);
            
            window.render(enemies[tofight]);
            window.display();
            
            if(enemies[tofight].gethealth()<=0){
                isInCombat = false;
                chancetofight = 0;
                enemies[tofight].sethealth(60);
                knight.setPosition(savedKnightX,savedKnightY);
                savedPosition = false;
            }
            
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
        RenderWindow losingscreen("Darkness Awaits",1280,720);
        bool lostgame = RenderLosing(losingscreen);
        if(!lostgame){
            losingscreen.cleanUp();
            SDL_Quit();
            return 0;
        }
    }

    return 0;

}