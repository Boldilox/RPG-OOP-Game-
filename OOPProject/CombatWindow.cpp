

// #include "CombatWindow.hpp"




// CombatWindow::CombatWindow() : window(nullptr), renderer(nullptr) {}

// CombatWindow::~CombatWindow() {
//     destroy();
// }

// void CombatWindow::create(int width, int height) {
//     window = SDL_CreateWindow("Combat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
//     if (window == nullptr) {
//          std::cout<<"Window failed to init. Error: "<< SDL_GetError()<<std::endl;
//     }

//     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
// }

// void CombatWindow::render(Entity& p_entity) {
//     SDL_Rect src;
//     src.x = p_entity.getCurrentFrame().x;
//     src.y = p_entity.getCurrentFrame().y;
//     src.w = p_entity.getCurrentFrame().w;
//     src.h = p_entity.getCurrentFrame().h;

//     SDL_Rect dst;
//     dst.x = p_entity.getX();
//     dst.y = p_entity.getY();

   

    
//      if (dynamic_cast<Knight*>(&p_entity) != nullptr){
//             dst.w = 64; // Adjust scale factor for the knight
//             dst.h = 64;
//             dst.y += (128 - dst.h);
//         } else {
//             dst.w = src.w;
//             dst.h = src.h;
//         }
    


// }

// void CombatWindow::destroy() {
//     if (renderer != nullptr) {
//         SDL_DestroyRenderer(renderer);
//         renderer = nullptr;
//     }
//     if (window != nullptr) {
//         SDL_DestroyWindow(window);
//         window = nullptr;
//     }
// }

// SDL_Texture* CombatWindow::loadTexture(const char* p_filePath) {
//     SDL_Texture* texture = NULL;
//     texture = IMG_LoadTexture(renderer,p_filePath);
//     if (texture==NULL){
//         std::cout<<"Failed to load a texture. Error: "<<SDL_GetError()<<std::endl;

//     }
//     return texture;
// }

// void CombatWindow::display(){
//     SDL_RenderPresent(renderer);
// }
