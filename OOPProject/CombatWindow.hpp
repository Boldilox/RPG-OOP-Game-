// // CombatWindow.hpp
// #ifndef COMBAT_WINDOW_HPP
// #define COMBAT_WINDOW_HPP

// // Forward declarations of SFML classes to reduce direct dependency in the header file
// namespace sf {
//     class RenderWindow;
//     class Texture;
//     class Sprite;
// }

// // CombatWindow class declaration
// class CombatWindow {
// public:
//     CombatWindow();   // Constructor
//     ~CombatWindow();  // Destructor to clean up resources
//     void run();       // Function to start the combat window

// private:
//     sf::RenderWindow* window;  // Pointer to the SFML window
//     sf::Texture* knightTexture;    // Pointer to the knight's texture
//     sf::Texture* enemyTexture;     // Pointer to the enemy's texture
//     sf::Sprite* knightSprite;      // Pointer to the knight's sprite
//     sf::Sprite* enemySprite;       // Pointer to the enemy's sprite

//     void loadTextures();   // Function to load textures
//     void createSprites();  // Function to create and position sprites
//     void gameLoop();       // Main game loop function
// };

// #endif // COMBAT_WINDOW_HPP
