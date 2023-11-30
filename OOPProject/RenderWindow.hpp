#pragma once
#include <SDL.h>
#include<SDL_image.h>

#include "Entity.hpp"
class RenderWindow{
public:
    RenderWindow(const char* p_title,int p_W,int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    void cleanUp();
    void clear();
    void render(Entity& p_entity);
    void display();
    void toggleCombatWindow();
    void createCombatWindow(int width, int height);
    bool isCharacterMovementPaused() const { return pauseCharacterMovement; }
    // Function to clean up combat window
    void cleanUpCombatWindow();
    bool pauseCharacterMovement;
    
private:
   
    SDL_Window* window;
    SDL_Renderer* renderer;
    

};